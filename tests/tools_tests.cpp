//
// dpw 2025.03.27
//
#include <catch2/catch_all.hpp>  // For Catch2 v3

#include <gitrepo/tools.hpp>
#include <gitrepo/version.hpp>


TEST_CASE("Test tools", "[version]") {
    const auto vers = gitrepo::Version();
    REQUIRE(vers.major == 0);
    REQUIRE(vers.minor == 2);
    REQUIRE(vers.patch >= 1);
    REQUIRE(vers.to_string() >= "0.1.0");
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

