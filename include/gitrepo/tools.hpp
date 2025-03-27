//
// dpw
//

#pragma once

namespace gitrepo::tools {
    constexpr auto VERSION = "0.2.0-101";

    struct GitRepo {
        std::string name;
        std::string branch;
        std::string status;
        std::string parent;
        std::string url;
        bool enabled;
    };

}
