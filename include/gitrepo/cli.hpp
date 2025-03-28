//
// dpw 2025-03-27 22:32:29
//

#pragma once

#include <cxxopts.hpp>

namespace gitrepo::cli {
    // set the config defaults here
    struct Config {
        std::string repo_home = ".gitrepo-tools";
        std::string config_file = "config.json";
        std::string cmd = "pull";
        bool skip = false;
    };

    Config parse(int argc, char* argv[]);
}  // namespace gitrepo::cli
