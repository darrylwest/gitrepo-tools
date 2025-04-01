//
// 2025-03-31 18:46:37 dpw
//

#pragma once

#include <gitrepo/cli.hpp>
#include <string>
#include <set>
#include <filesystem>

namespace gitrepo::config {
    namespace fs = std::filesystem;

    struct Config {
        std::string version;
        std::string home_folder;
        std::set<fs::path> excludes;
        bool verbose;
    };

    Config parse_config(const cli::CLI& ctx);
}  // namespace gitrepo::config
