//
// 2025-03-31 18:46:37 dpw
//

#include <spdlog/spdlog.h>

#include <filesystem>
#include <fstream>
#include <gitrepo/config.hpp>
#include <nlohmann/json.hpp>

namespace gitrepo::config {
    namespace fs = std::filesystem;
    using json = nlohmann::json;

    Config parse_config(const cli::CLI& ctx) {
        Config config;

        fs::path repo_home = ctx.repo_home;  // Assuming ctx.repo_home is convertible
        fs::path config_file = ctx.config_file;
        fs::path path = repo_home / config_file;

        // parse the file
        try {
            // Open the file for reading
            std::ifstream json_file(path);
            if (!json_file) {
                throw std::runtime_error("Failed to open config file: " + path.string());
            }

            // Parse JSON file
            nlohmann::json json_data;
            json_file >> json_data;

            // Use JSON data to populate the Config object
            // Assuming 'Config' has fields that reflect the JSON structure
            config.version = json_data.at("version").get<decltype(config.version)>();
            config.home_folder = json_data.at("home_folder").get<decltype(config.home_folder)>();
            config.verbose = json_data.at("verbose").get<decltype(config.verbose)>();
            // Add more fields as needed...

            // Check if "excludes" key exists and is an array
            if (json_data.contains("excludes") && json_data["excludes"].is_array()) {
                for (const auto& item : json_data["excludes"]) {
                    if (item.is_string()) {
                        config.excludes.emplace_back(item.get<std::string>());
                        spdlog::info("excludes '{}'", item.get<std::string>());
                    }
                }
            }

        } catch (const nlohmann::json::exception& e) {
            spdlog::error("JSON parsing error: {}", e.what());
        } catch (const std::exception& e) {
            spdlog::error("Error reading config file: {}", e.what());
        }

        return config;
    }
}  // namespace gitrepo::config
