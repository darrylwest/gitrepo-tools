//
// 2025-04-04 15:08:06 dpw
//

#include <catch2/catch_all.hpp>  // For Catch2 v3
#include <gitrepo/data.hpp>

#include <spdlog/spdlog.h>

// namespace fs = std::filesystem;
using namespace gitrepo::data;

TEST_CASE("Data tests", "[data-read]") {
    spdlog::set_level(spdlog::level::critical);
    std::string datafile = "./data/repos-test.db";
    auto repo = read_repos_db(datafile);
    REQUIRE(repo.size() > 26);
}

TEST_CASE("Data tests", "[data-write]") {
    spdlog::set_level(spdlog::level::critical);
    std::string datafile = "./data/repos-test.db";
    auto repos = read_repos_db(datafile);
    datafile = "./data/repos-test-copy.db";
    auto count = write_repos_db(datafile, repos);
    REQUIRE(count == repos.size());
    spdlog::set_level(spdlog::level::critical);
}


