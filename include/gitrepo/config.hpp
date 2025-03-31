//
// 2025-03-31 18:46:37 dpw
//

#pragma once

#include <gitrepo/cli.hpp>
#include <string>

namespace gitrepo::config {
    struct Config {
        std::string version;
        std::string home_folder;
        bool verbose;
    };

    Config parse_config(const cli::CLI& ctx);
}  // namespace gitrepo::config
