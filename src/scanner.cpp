//
// 2025-03-31 18:46:37 dpw
//

#include <gitrepo/scanner.hpp>
#include <filesystem>
#include <vector>
#include <set>
#include <spdlog/spdlog.h>

namespace gitrepo::scanner {
    namespace fs = std::filesystem;

    void scan(const fs::path& folder, std::vector<fs::path>& folders, const std::set<fs::path>& excludes) {
        for (auto& entry : fs::directory_iterator(folder)) {
            auto file = fs::path(entry).append(".git");
            if (fs::exists(file)) {
                std::string fstr = file.string();
                spdlog::info("git repo: {}", fstr);
                folders.push_back(entry);
            }

            if (fs::is_directory(entry) && excludes.find(entry) == excludes.end()) {
                scan(entry, folders, excludes);
            }
        }
    }

    std::vector<fs::path> scan_folders(const config::Config& config) {
        fs::path home = std::getenv("HOME");
        auto folder = fs::path(home / config.home_folder);
        std::set<fs::path> excludes;
        std::vector<fs::path> folders;

        scan(folder, folders, excludes);

        return folders;
    }
}
