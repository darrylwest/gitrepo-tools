//
// dpw
//

#include <filesystem>
#include <fstream>
#include <gitrepo/tools.hpp>
#include <stdexcept>
#include <string>
#include <array>

#include "spdlog/spdlog.h"

namespace gitrepo::tools {
    namespace fs = std::filesystem;

    const auto GIT_HEAD = fs::path("HEAD");
    const auto GIT_CONFIG = fs::path("config");
    constexpr auto CLEAN = "clean";
    constexpr auto DIRTY = "dirty";

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
        fs::path config_path(repo_root / GIT_CONFIG);
        std::ifstream configFile(config_path.string());
        if (!configFile.is_open()) {
            throw std::runtime_error("Could not open .git/config file.");
        }

        std::string line;
        while (std::getline(configFile, line)) {
            if (line.find("[remote \"origin\"]") != std::string::npos) {
                // Read the next line to find the URL
                if (std::getline(configFile, line) && line.find("url = ") != std::string::npos) {
                    return line.substr(7); // Skip "url = "
                }
            }
        }

        return ""; // Return empty if no URL found
    }

    std::string exec(const std::string& repo_root, const std::string& command) {
        std::array<char, 256> buffer{};
        std::string cmd = "git -C " + repo_root + " " + command;
        std::string result;

        FILE *fp;
        fp = popen(cmd.c_str(), "r");
        if (!fp) {
            spdlog::error("popen() failed!");
            throw std::runtime_error("popen() failed!");
        }

        while (fgets(buffer.data(), buffer.size(), fp) != nullptr) {
            result += buffer.data();
        }

        pclose(fp);

        return result;
    }

    std::string get_status(const std::string& repo_root) {
        spdlog::debug("get_status: {}", repo_root);
        auto status = exec(repo_root, "status -s");
        spdlog::debug("status: {} len: {}", status, status.size());
        return status.empty() ? CLEAN : DIRTY;
    }

    GitRepo scan_repo(const std::string& path) {
        const auto git_root = path + "/.git";

        GitRepo repo;

        size_t last = path.find_last_of('/');
        if (last != std::string::npos) {
            repo.name = path.substr(last + 1);
        } else {
            repo.name = path;
        }

        repo.branch = get_active_branch(git_root);
        repo.status = get_status(path);
        repo.parent = path;
        repo.url = get_remote_url(git_root);
        repo.enabled = true;

        return repo;
    }

    CommandResponse run_job(const GitRepo& repo, const std::string& command) {
        CommandResponse response;
        response.repo = repo;
        response.cmd = command;

        response.output = exec(repo.parent, command);

        return response;
    }
}
