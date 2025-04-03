//
// dpw
//

#include <spdlog/spdlog.h>

#include <gitrepo/cli.hpp>
#include <gitrepo/config.hpp>
#include <gitrepo/scanner.hpp>
#include <gitrepo/tools.hpp>
#include <future>
#include <vector>


int main(int argc, char **argv) {
    spdlog::set_level(spdlog::level::info);

    auto ctx = gitrepo::cli::parse(argc, argv);

    if (ctx.skip) {
        return 0;
    }

    spdlog::info("context: {}", ctx.to_string());

    auto config = gitrepo::config::parse_config(ctx);

    spdlog::info("config home: {}", config.home_folder);

    // process the command on each repo, one thread per process
    auto folders = gitrepo::scanner::scan_folders(config);
    spdlog::info("folder count: {}", folders.size());

    std::vector<std::future<gitrepo::tools::CommandResponse>> jobs;
    jobs.reserve(folders.size());
    for (const auto& folder : folders) {
        spdlog::debug("folder: {}", folder.c_str());
        const auto repo = gitrepo::tools::scan_repo(folder);
        spdlog::info("repo: {}", repo.to_json().dump());

        if (repo.status != "clean" || repo.url.empty()) {
            continue;
        }

        // execute the command in a separate thread
        jobs.push_back(std::async(std::launch::async, gitrepo::tools::run_job, repo, ctx.cmd));
    }

    std::vector<gitrepo::tools::CommandResponse> results;
    for (auto& job : jobs) {
        results.push_back(job.get());
    }

    for (const auto& result : results) {
        spdlog::info("{}: {}: {}", result.repo.name, result.cmd, result.output);
    }

    return 0;
}
