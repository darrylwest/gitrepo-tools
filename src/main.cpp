//
// dpw
//

#include <spdlog/spdlog.h>

#include <gitrepo/cli.hpp>
// #include <gitrepo/tools.hpp>
// #include <domainkeys/keys.hpp>
// #include <quickkv/quickkv.hpp>

int main(int argc, char **argv) {
    spdlog::set_level(spdlog::level::info);

    auto config = gitrepo::cli::parse(argc, argv);

    if (config.skip) {
        return 0;
    }

    spdlog::info("config: repo home: {}, config file: {}, command: {}",
        config.repo_home,
        config.config_file,
        config.cmd
    );

    return 0;
}
