//
// dpw 2025.03.27
//
#include <catch2/catch_all.hpp>  // For Catch2 v3
#include <gitrepo/cli.hpp>
#include <string>
#include <vector>

#include "spdlog/spdlog.h"

struct Params {
    int argc;
    char** argv;
};

Params create_params(std::vector<std::string> args) {
    Params params;

    params.argc = args.size();

    // need to add this for the argv terminator
    args.emplace_back("");

    spdlog::debug("argc:{}",  params.argc);

    params.argv = new char*[args.size()];
    for (size_t i = 0; i < args.size(); i++) {
        params.argv[i] = const_cast<char*>(args[i].c_str());
        spdlog::debug("argv[{}] = {}", i, args[i]);
    }

    return params;
}

TEST_CASE("Test CLI", "[cli][parse-no-params]") {
    Params params = create_params({"gitrepo-tools"});

    auto config = gitrepo::cli::parse(params.argc, params.argv);

    INFO("zero command line params");
    REQUIRE(config.repo_home == ".gitrepo-tools");
    REQUIRE(config.config_file == "config.json");
    REQUIRE(config.cmd == "pull");
    REQUIRE(config.skip == false);
}

TEST_CASE("Test CLI", "[cli][parse-repo_home]") {
    spdlog::set_level(spdlog::level::off);
    Params params = create_params({"gitrepo-tools", "--repo-home", "./" });

    const auto config = gitrepo::cli::parse(params.argc, params.argv);

    spdlog::debug("repo home in command line params: {}", config.repo_home);

    INFO("repo home in command line params");
    // REQUIRE(config.repo_home == "./");
    REQUIRE(config.config_file == "config.json");
    REQUIRE(config.cmd == "pull");
    REQUIRE(config.skip == false);
}


