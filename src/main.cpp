//
// dpw
//

#include <spdlog/spdlog.h>
#include <filesystem>
#include <fstream>
#include <future>
#include <gitrepo/cli.hpp>
#include <gitrepo/config.hpp>
#include <gitrepo/scanner.hpp>
#include <gitrepo/tools.hpp>
#include <vector>
#include <nlohmann/json.hpp>

int main(int argc, char** argv) {
    using json = nlohmann::json;

    spdlog::set_level(spdlog::level::info);

    auto ctx = gitrepo::cli::parse(argc, argv);

    if (ctx.skip) {
        return 0;
    }

    spdlog::info("context: {}", ctx.to_string());

    auto config = gitrepo::config::parse_config(ctx);

    spdlog::info("config home: {}", config.home_folder);

    std::vector<gitrepo::tools::GitRepo> repos;
    auto j = json::array();
    auto db_filename = ctx.repo_home + "/data/repos.db";

    if (ctx.skip_scan) {
        // read from the database
        spdlog::info("skip scan and read the repo database");
    } else {
        auto folders = gitrepo::scanner::scan_folders(config);
        spdlog::info("folder count: {}", folders.size());

        for (const auto& folder : folders) {
            spdlog::debug("folder: {}", folder.c_str());
            const auto repo = gitrepo::tools::scan_repo(folder);
            spdlog::info("repo: {}", repo.to_json().dump());

            if (repo.status != "clean" || repo.url.empty()) {
                continue;
            }

            repos.emplace_back(repo);
            j.push_back(repo.to_json());
        }

        // now write them out to the data file...
        std::ofstream file(db_filename);
        if (!file) {
            spdlog::error("Failed to open file {}", db_filename);
        } else {
            file << j.dump(4);
            file.close();
        }
    }

    std::vector<std::future<gitrepo::tools::CommandResponse>> jobs;
    jobs.reserve(repos.size());
    for (const auto& repo : repos) {
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
