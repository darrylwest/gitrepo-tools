//
// dpw
//

#pragma once

#include <filesystem>
#include <gitrepo/cli.hpp>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace gitrepo::tools {
    using json = nlohmann::json;

    struct GitRepo {
        std::string name;
        std::string branch;
        std::string status;
        std::string parent;
        std::string url;
        bool enabled;

        // Member function to convert GitRepo to JSON
        nlohmann::json to_json() const {
            return nlohmann::json{{"name", name},     {"branch", branch}, {"status", status},
                                  {"parent", parent}, {"url", url},       {"enabled", enabled}};
        }
    };

    const GitRepo from_json(const json& item);

    struct CommandResponse {
        GitRepo repo;
        std::string cmd;
        std::string output;
        std::string error;
    };

    // scan repo to determine brand, status, name, url
    GitRepo scan_repo(const std::string& path);

    // recursively scan all folders for repos and return a vector of GitRepo structs
    std::vector<GitRepo> scan_folders(const gitrepo::cli::CLI& ctx);

    // run a command and return the response
    CommandResponse run_command(const GitRepo& repo, const std::string& command);

    // return the current active branch for the current repo
    std::string get_active_branch(const std::string& repo_folder);

    // return the origin url from the repos config file
    std::string get_remote_url(const std::string& repo_folder);

    // return dirty or clean base on the repos status
    std::string get_status(const std::string& repo_folder);

    // execute the git command
    std::string exec(const std::string& repo_folder, const std::string& command);

    CommandResponse run_job(const GitRepo& repo, const std::string& command);

}  // namespace gitrepo::tools
