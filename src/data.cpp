//
// 2025-04-04 15:08:06 dpw
//

#include <spdlog/spdlog.h>

#include <gitrepo/data.hpp>
#include <nlohmann/json.hpp>

namespace gitrepo::data {
    using json = nlohmann::json;

    // read the data file, parse the json and return a vector of GitRepo objects
    std::vector<tools::GitRepo> read_repos_db(const std::string& datafile) {
        spdlog::info("reading repos from {}", datafile);
        std::vector<tools::GitRepo> repos;

        return repos;
    }

    // write repo data to file as json and return the number of rows written
    size_t write_repos_db(const std::string& datafile, std::vector<tools::GitRepo>& repos) {
        spdlog::info("writing repos to {}", datafile);
        return repos.size();
    }
}  // namespace gitrepo::data
