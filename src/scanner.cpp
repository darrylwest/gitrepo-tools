//
// 2025-03-31 18:46:37 dpw
//

#include <spdlog/spdlog.h>

#include <filesystem>
#include <gitrepo/scanner.hpp>
#include <ranges>
#include <set>
#include <vector>

namespace gitrepo::scanner {
    namespace fs = std::filesystem;

    bool should_exclude(const std::string& path, const std::vector<std::string>& excludes) {
        return std::ranges::any_of(excludes, [&path](const std::string& exclude) {
            return path.contains(exclude);
        });
    }

    void scan(const fs::path& folder, std::vector<fs::path>& folders,
              const std::vector<std::string>& excludes) {
        for (auto& entry : fs::directory_iterator(folder)) {
            // first do the excludes
            if (entry.is_regular_file()) {
                continue;
            }

            if (should_exclude(entry.path().string(), excludes)) {
                continue;
            }

            auto file = fs::path(entry).append(".git");
            if (fs::exists(file)) {
                std::string fstr = file.string();
                spdlog::debug("git repo: {}", fstr);
                folders.push_back(entry);
            }

            if (fs::is_directory(entry)) {
                scan(entry, folders, excludes);
            }
        }
    }

    std::vector<fs::path> scan_folders(const config::Config& config) {
        fs::path home = std::getenv("HOME");
        auto folder = fs::path(home / config.home_folder);
        std::vector<fs::path> folders;

        scan(folder, folders, config.excludes);

        return folders;
    }
}  // namespace gitrepo::scanner
