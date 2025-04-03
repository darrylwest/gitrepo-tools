//
// dpw 2025-03-27 22:32:29
//

#include <cxxopts.hpp>
#include <gitrepo/cli.hpp>
#include <gitrepo/tools.hpp>
#include <gitrepo/version.hpp>

namespace gitrepo::cli {

    CLI parse(int argc, char* argv[]) {
        CLI ctx;

        try {
            cxxopts::Options options(argv[0], "A command line tool for managing git repos");

            // clang-format off
            options.add_options()
                ("v,version", "Show the current version")
                ( "h,help", "Show this help")
                ("r,repo-home", "Set the repo home folder", cxxopts::value<std::string>())
                ("c,command", "The command to run on all repos", cxxopts::value<std::string>())
                ("s,skip-scan", "skip file scan and read from data file", cxxopts::value<bool>())
                ( "config", "The configuration file", cxxopts::value<std::string>()
            );

            // clang-format on
            auto result = options.parse(argc, argv);

            if (result.count("version")) {
                const auto version = gitrepo::Version();
                std::cout << argv[0] << " Version: " << version << '\n';
                ctx.skip = true;
            }

            if (result.count("help")) {
                std::cout << options.help() << '\n';
                ctx.skip = true;
            }

            if (result.count("repo-home")) {
                ctx.repo_home = result["repo-home"].as<std::string>();
            }

            if (result.count("command")) {
                ctx.cmd = result["command"].as<std::string>();
            }

            if (result.count("skip-scan")) {
                ctx.skip_scan = true;
            }

            if (result.count("config")) {
                ctx.config_file = result["config"].as<std::string>();
            }
        } catch (const cxxopts::OptionException& e) {
            std::cout << "error parsing options: " << e.what() << '\n';
            ctx.skip = true;
        }

        return ctx;
    }
}  // namespace gitrepo::cli
