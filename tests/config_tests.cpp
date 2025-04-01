//
// 2025-03-31 18:46:37 dpw
//

#include <catch2/catch_all.hpp>  // For Catch2 v3
#include <string>
#include <gitrepo/cli.hpp>
#include <gitrepo/config.hpp>

TEST_CASE("Config Tests", "[config]") {
    REQUIRE(true);
    const gitrepo::cli::CLI ctx{
        .repo_home = "./",
        .config_file = "config/config.json",
        .cmd = "pull",
        .skip = false,
    };

    auto config = gitrepo::config::parse_config(ctx);

    REQUIRE(config.version >= "0.1.0-100");
    REQUIRE(config.home_folder == "raincity");
    REQUIRE(config.verbose == false);
    REQUIRE(config.excludes.size() > 1);

    // logging
    // skip folders

}

