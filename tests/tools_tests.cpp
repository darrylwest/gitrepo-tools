//
// dpw 2025.03.27
//
#include <catch2/catch_all.hpp>  // For Catch2 v3
#include <gitrepo/tools.hpp>
#include <gitrepo/version.hpp>

#include <spdlog//spdlog.h>

// namespace fs = std::filesystem;

const std::string test_repo = "tests/test-repo";

TEST_CASE("Tools tests", "[version]") {
    const auto vers = gitrepo::Version();
    REQUIRE(vers.major == 0);
    REQUIRE(vers.minor == 2);
    REQUIRE(vers.patch >= 1);
    REQUIRE(vers.to_string() >= "0.1.0");
}

TEST_CASE("Tools tests", "[tools][repo-struct]") {
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

TEST_CASE("Tools tests", "[tools][get_active_branch]") {
    spdlog::set_level(spdlog::level::info);
    const auto branch = gitrepo::tools::get_active_branch(test_repo);

    spdlog::info("active branch: {}", branch);

    REQUIRE(branch == "develop");
}

TEST_CASE("Tools tests", "[tools][get_remote_url]") {
    REQUIRE(true);
}

TEST_CASE("Tools tests", "[tools][get_status]") {
    REQUIRE(true);
}

