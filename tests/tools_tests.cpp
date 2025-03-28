//
// dpw 2025.03.27
//
#include <catch2/catch_all.hpp>  // For Catch2 v3

#include <gitrepo/tools.hpp>


TEST_CASE("Test tools", "[version]") {
    const auto vers = gitrepo::tools::VERSION;
    REQUIRE(vers == gitrepo::tools::VERSION);
}

TEST_CASE("Test tools", "[tools][repo-struct]") {
    auto repo = gitrepo::tools::GitRepo{
        .name = "test",
        .branch = "develop",
        .status = "clean",
        .parent = "/some/path",
        .url = "https://github.com/dpw/test.git",
        .enabled = true,
    };

    REQUIRE(true);
}

