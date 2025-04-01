//
// dpw 2025-03-27 22:32:29
//

#pragma once

#include <cxxopts.hpp>

#include "spdlog/fmt/bundled/format.h"

namespace gitrepo::cli {
    // TODO add extended help here
    // set the config defaults here
    struct CLI {
        std::string repo_home = ".gitrepo-tools";        // store date, logs, config
        std::string config_file = "config/config.json";  // look in repo_home, ~/.config/gitrepo-tools, etc
        std::string cmd = "pull";
        bool skip = false;

        // show the important attributes
        [[nodiscard]] auto to_string() const {
            return fmt::format("repo_home: {}, config_file: {}, cmd: {}", repo_home, config_file, cmd);
        }
    };

    CLI parse(int argc, char* argv[]);
}  // namespace gitrepo::cli
