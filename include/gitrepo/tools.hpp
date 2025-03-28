//
// dpw
//

#pragma once

#include <catch2/catch_config.hpp>
#include <filesystem>

namespace gitrepo::tools {
    constexpr auto VERSION = "0.2.0-103";

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
    std::vector<GitRepo> scan_folders(const cli::Config& config);

    // run a command and return the response
    CommandResponse run_command(const GitRepo& repo, const std::string& command);

}  // namespace gitrepo::tools
