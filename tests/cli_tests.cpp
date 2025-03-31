//
// dpw 2025.03.27
//
#include <catch2/catch_all.hpp>  // For Catch2 v3
#include <gitrepo/cli.hpp>
#include <string>
#include <vector>
#include <functional>

#include "spdlog/spdlog.h"

namespace helpers {

    inline std::string capture_stdout(const std::function<void()>& func) {
        std::ostringstream oss;
        std::streambuf* old_cout = std::cout.rdbuf(oss.rdbuf());  // Redirect std::cout

        func();  // Execute function that prints to stdout

        std::cout.rdbuf(old_cout);  // Restore std::cout
        return oss.str();
    }
}

gitrepo::cli::CLI call_parse_cli(const std::vector<std::string>& args) {
    std::vector<char*> argv;
    argv.push_back(const_cast<char*>("gitrepo-tools"));

    for (auto& arg : args) {
        argv.push_back(const_cast<char*>(arg.c_str()));
    }
    argv.push_back(nullptr);

    auto argc = static_cast<int>(argv.size() - 1);

    return gitrepo::cli::parse(argc, argv.data());
}

TEST_CASE("Test CLI", "[cli][parse-no-params]") {
    std::vector<char*> argv;

    auto ctx = call_parse_cli({});

    INFO("zero command line params");
    REQUIRE(ctx.repo_home == ".gitrepo-tools");
    REQUIRE(ctx.config_file == "config/config.json");
    REQUIRE(ctx.cmd == "pull");
    REQUIRE(ctx.skip == false);
}

TEST_CASE("Test CLI", "[cli][parse-repo_home]") {
    const auto ctx = call_parse_cli({"gitrepo-tools", "--repo-home", "./" });

    spdlog::debug("repo home in command line params: {}", ctx.repo_home);

    INFO("repo home in command line params");
    REQUIRE(ctx.repo_home == "./");
    REQUIRE(ctx.config_file == "config/config.json");
    REQUIRE(ctx.cmd == "pull");
    REQUIRE(ctx.skip == false);
}

TEST_CASE("Test CLI", "[cli][parse-ctx]") {
    const auto ctx = call_parse_cli({"gitrepo-tools", "--config", "cfg.toml" });

    spdlog::debug("repo home in command line params: {}", ctx.repo_home);

    INFO("repo home in command line params");
    REQUIRE(ctx.repo_home == ".gitrepo-tools");
    REQUIRE(ctx.config_file == "cfg.toml");
    REQUIRE(ctx.cmd == "pull");
    REQUIRE(ctx.skip == false);
}

TEST_CASE("Test CLI", "[cli][parse-command]") {
    const auto ctx = call_parse_cli({"gitrepo-tools", "--command", "push" });

    spdlog::debug("repo home in command line params: {}", ctx.repo_home);

    INFO("repo home in command line params");
    REQUIRE(ctx.repo_home == ".gitrepo-tools");
    REQUIRE(ctx.config_file == "config/config.json");
    REQUIRE(ctx.cmd == "push");
    REQUIRE(ctx.skip == false);
}

TEST_CASE("Test CLI", "[cli][parse-help]") {
    const auto output = helpers::capture_stdout([]() {
        const std::function<void(int code)>shutdown = [](int code) {
            INFO("return code should be zero");
            REQUIRE(code == 0);
        };

        const auto ctx = call_parse_cli({"gitrepo-tools", "--help", });

        INFO("repo home in command line params");
        REQUIRE(ctx.repo_home == ".gitrepo-tools");
        REQUIRE(ctx.config_file == "config/config.json");
        REQUIRE(ctx.cmd == "pull");
        REQUIRE(ctx.skip == true);
    });

    INFO(output);
    REQUIRE(output.find("command line") != std::string::npos);
}

TEST_CASE("Test CLI", "[cli][parse-version]") {
    const auto output = helpers::capture_stdout([]() {
        const std::function<void(int code)>shutdown = [](int code) {
            INFO("return code should be zero");
            REQUIRE(code == 0);
        };

        const auto ctx = call_parse_cli({"gitrepo-tools", "--version", });

        INFO("repo home in command line params");
        REQUIRE(ctx.repo_home == ".gitrepo-tools");
        REQUIRE(ctx.config_file == "config/config.json");
        REQUIRE(ctx.cmd == "pull");
        REQUIRE(ctx.skip == true);
    });

    INFO(output);
    REQUIRE(output.find("Version:") != std::string::npos);
}

TEST_CASE("Test CLI", "[cli][parse-bad-param]") {
    const auto output = helpers::capture_stdout([]() {
        const std::function<void(int code)>shutdown = [](int code) {
            INFO("return code should be zero");
            REQUIRE(code == 0);
        };

        const auto ctx = call_parse_cli({"gitrepo-tools", "--bad-flag", });

        INFO("repo home in command line params");
        REQUIRE(ctx.repo_home == ".gitrepo-tools");
        REQUIRE(ctx.config_file == "config/config.json");
        REQUIRE(ctx.cmd == "pull");
        REQUIRE(ctx.skip == true);
    });

    INFO(output);
    REQUIRE(output.find("error parsing") != std::string::npos);
}
