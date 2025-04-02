//
// dpw
//

#include <gitrepo/config.hpp>
#include <gitrepo/tools.hpp>
#include <fstream>
#include <stdexcept>
#include <filesystem>

namespace gitrepo::tools {
    namespace fs = std::filesystem;

    const auto GIT_HEAD = fs::path("HEAD");
    const auto GIT_CONFIG = fs::path("config");

    std::string get_active_branch(const std::string& repo_root) {
        fs::path head_path(repo_root / GIT_HEAD);
        std::ifstream headFile(head_path.string());
        if (!headFile.is_open()) {
            throw std::runtime_error("Could not open .git/HEAD file.");
        }

        std::string line;
        if (std::getline(headFile, line)) {
            if (line.find("ref:") == 0) {
                std::string branch = line.substr(5); // Skip "ref: "

                size_t last = branch.find_last_of('/');
                if (last != std::string::npos) {
                    return branch.substr(last + 1);
                }
            }
        }

        return ""; // Return empty if no branch found
    }

    std::string get_remote_url(const std::string& repo_root) {
        fs::path config_path(repo_root / GIT_HEAD);
        std::ifstream configFile(config_path.string());
        if (!configFile.is_open()) {
            throw std::runtime_error("Could not open .git/config file.");
        }

        std::string line;
        while (std::getline(configFile, line)) {
            if (line.find("[remote \"origin\"]") != std::string::npos) {
                // Read the next line to find the URL
                if (std::getline(configFile, line) && line.find("url = ") != std::string::npos) {
                    return line.substr(6); // Skip "url = "
                }
            }
        }

        return ""; // Return empty if no URL found
    }

    std::string get_status() {
        std::string status;
        // Check for untracked files and changes in the working directory
        // This is a simple check; for a full status, you would need to read the index and working directory.
        // Here we just check for untracked files as an example.
        std::filesystem::path gitDir(".git");
        for (const auto& entry : std::filesystem::directory_iterator(gitDir.parent_path())) {
            if (entry.path() != gitDir && entry.path() != gitDir.parent_path() / ".git") {
                status += entry.path().filename().string() + " (untracked)\n";
            }
        }

        return status.empty() ? "No changes" : status;
    }

    GitRepo scan_repo(const std::string& path) {
        GitRepo repo;
        repo.name = path;

        return repo;
    }
}
