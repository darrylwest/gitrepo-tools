//
// dpw
//

#include <spdlog/spdlog.h>

#include <filesystem>
#include <fstream>
#include <future>
#include <gitrepo/cli.hpp>
#include <gitrepo/config.hpp>
#include <gitrepo/data.hpp>
#include <gitrepo/scanner.hpp>
#include <gitrepo/tools.hpp>
#include <nlohmann/json.hpp>
#include <vector>

int main(int argc, char** argv) {
    using namespace gitrepo;

    spdlog::set_level(spdlog::level::info);

    auto ctx = cli::parse(argc, argv);

    // cli detected a help or version switch, so exit
    if (ctx.skip) {
        return 0;
    }

    spdlog::info("context: {}", ctx.to_string());

    auto config = config::parse_config(ctx);

    spdlog::info("config home: {}", config.home_folder);

    auto db_filename = ctx.repo_home + "/data/repos.db";
    // find the last update timestamp to determine to skip scan
    auto repos = data::read_repos_db(db_filename);

    if (!ctx.skip_scan) {
        repos.clear();
        auto folders = scanner::scan_folders(config);
        spdlog::info("folder count: {}", folders.size());

        for (const auto& folder : folders) {
            spdlog::debug("folder: {}", folder.c_str());
            const auto repo = tools::scan_repo(folder);
            spdlog::info("repo: {}", repo.to_json().dump());

            if (repo.status != "clean" || repo.url.empty()) {
                continue;
            }

            repos.emplace_back(repo);
        }

        auto count = data::write_repos_db(db_filename, repos);
        if (count == repos.size()) {
            spdlog::info("repo db size: {}", count);
        } else {
            spdlog::error("repo db size: {}", count);
        }
    }

    std::vector<std::future<tools::CommandResponse>> jobs;
    jobs.reserve(repos.size());
    for (const auto& repo : repos) {
        // execute the command in a separate thread
        jobs.push_back(std::async(std::launch::async, tools::run_job, repo, ctx.cmd));
    }

    std::vector<tools::CommandResponse> results;
    for (auto& job : jobs) {
        results.push_back(job.get());
    }

    for (const auto& result : results) {
        spdlog::info("{}: {}: {}", result.repo.name, result.cmd, result.output);
    }

    return 0;
}
