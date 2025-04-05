//
// 2025-04-04 15:08:06 dpw
//

#include <spdlog/spdlog.h>

#include <filesystem>
#include <fstream>
#include <gitrepo/data.hpp>
#include <nlohmann/json.hpp>
#include <sstream>
#include <vector>
#include <quickkv/quickkv.hpp>
#include <domainkeys/keys.hpp>
#include <filesystem>

namespace gitrepo::data {
    using json = nlohmann::json;
    namespace fs = std::filesystem;

    // read the data file, parse the json and return a vector of GitRepo objects
    std::vector<tools::GitRepo> read_repos_db(const std::string& datafile) {
        spdlog::info("reading repos from {}", datafile);
        std::vector<tools::GitRepo> repos;
        auto path = fs::path(datafile);

        quickkv::KVStore store;
        store.read(path);

        // now create the repos vector
        for (const auto& key : store.keys()) {
            spdlog::debug("reading key {}", key);
            auto response = store.get(key);
            if (response) {
                auto jval = json::parse(response.value());
                repos.emplace_back(tools::from_json(jval));
            } else {
                spdlog::error("response is bad");
            }
        }

        return repos;
    }

    // write repo data to file as json and return the number of rows written
    size_t write_repos_db(const std::string& datafile, std::vector<tools::GitRepo>& repos) {
        spdlog::info("writing repos to {}", datafile);

        quickkv::KVStore store;
        for (const tools::GitRepo& repo : repos) {
            auto key = domainkeys::keys::create_timestamp_key();
            store.set(key.to_string(), repo.to_json().dump());
        }

        if (store.write(datafile)) {
            return store.size();
        }

        spdlog::error("failed to write repo database {}", datafile);
        return 0;
    }
}  // namespace gitrepo::data
