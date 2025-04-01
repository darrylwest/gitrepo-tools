//
// 2025-03-31 18:46:37 dpw
//

#include <catch2/catch_all.hpp>  // For Catch2 v3
#include <string>
#include <gitrepo/scanner.hpp>
#include <gitrepo/config.hpp>
#include <filesystem>
#include <spdlog/spdlog.h>

namespace fs = std::filesystem;

TEST_CASE("Scanner Tests", "[scanner]") {
    const gitrepo::cli::CLI ctx{
        .repo_home = "./",
        .config_file = "config/config.json",
        .cmd = "pull",
        .skip = false,
    };

    auto config = gitrepo::config::parse_config(ctx);
    // spdlog::set_level(spdlog::level::info);
    auto folders = gitrepo::scanner::scan_folders(config);
    spdlog::info("repo count: {}", folders.size());

    INFO("repo count should be > 5");
    REQUIRE(folders.size() > 5);
}

