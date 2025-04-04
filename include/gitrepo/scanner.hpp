//
// 2025-03-31 18:46:37 dpw
//

#pragma once

#include <filesystem>
#include <gitrepo/config.hpp>
#include <vector>

namespace gitrepo::scanner {
    namespace fs = std::filesystem;

    std::vector<fs::path> scan_folders(const config::Config& config);
}  // namespace gitrepo::scanner
