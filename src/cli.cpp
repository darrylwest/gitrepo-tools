//
// dpw 2025-03-27 22:32:29
//

#include <cxxopts.hpp>
#include <gitrepo/cli.hpp>
#include <gitrepo/tools.hpp>

namespace gitrepo::cli {

    Config parse(int argc, char* argv[]) {
        Config config;

        try {
            cxxopts::Options options(argv[0], "A command line tool for managing git repos");

            options.add_options()("v,version", "Show the current version")(
                "h,help", "Show this help")("c,command", "The command to run on all repos",
                                            cxxopts::value<std::string>())(
                "config", "The configuration file", cxxopts::value<std::string>());

            auto result = options.parse(argc, argv);

            if (result.count("version")) {
                std::cout << argv[0] << " Version: " << gitrepo::tools::VERSION << std::endl;
                config.skip = true;
            }

            if (result.count("help")) {
                std::cout << options.help() << std::endl;
                config.skip = true;
            }

            if (result.count("command")) {
                config.cmd = result["command"].as<std::string>();
            }

            if (result.count("config")) {
                config.config_file = result["config"].as<std::string>();
            }
        } catch (const cxxopts::OptionException& e) {
            std::cout << "error parsing options: " << e.what() << std::endl;
            config.skip = true;
        }

        return config;
    }
}  // namespace gitrepo::cli
