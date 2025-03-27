//
// dpw 2025.03.27
//
#include <catch2/catch_all.hpp>  // For Catch2 v3

#include <gitrepo/cli.hpp>
#include <vector>
#include <string>

TEST_CASE("Test CLI", "[cli][parse-no-params]") {
    int argc = 1;
    std::vector<char*> argv;
    argv.emplace_back(const_cast<char*>("gitrepo-tools"));
    argv.push_back(nullptr);

    auto config = gitrepo::cli::parse(argc, argv.data());

    REQUIRE(config.repo_home == ".gitrepo-tools");
    REQUIRE(config.config_file == "config.json");
    REQUIRE(config.cmd == "pull");
    REQUIRE(config.skip == false);

}

