//
// 2025-04-04 15:08:06 dpw
//

#pragma once

#include <gitrepo/tools.hpp>
#include <vector>

namespace gitrepo::data {

    // read the data file, parse the json and return a vector of GitRepo objects
    std::vector<tools::GitRepo> read_repos_db(const std::string& datafile);

    // write repo data to file as json and return the number of rows written
    size_t write_repos_db(const std::string& datafile, std::vector<tools::GitRepo>& repos);

}  // namespace gitrepo::data
