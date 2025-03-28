//
// dpw
//

#pragma once

#include <filesystem>
#include <gitrepo/cli.hpp>
#include <string>
#include <vector>

namespace gitrepo::tools {
    constexpr auto VERSION = "0.2.1-106";

    struct GitRepo {
        std::string name;
        std::string branch;
        std::string status;
        std::string parent;
        std::string url;
        bool enabled;
    };

    struct CommandResponse {
        int exit_code;
        std::string output;
        std::string error;
    };

    // scan repo to determine brand, status, name, url
    GitRepo scan_repo(const std::string& path);

    // recursively scan all folders for repos and return a vector of GitRepo structs
    std::vector<GitRepo> scan_folders(const gitrepo::cli::Config& config);

    // run a command and return the response
    CommandResponse run_command(const GitRepo& repo, const std::string& command);

}  // namespace gitrepo::tools
