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

    auto ctx = gitrepo::cli::parse(argc, argv);

    if (ctx.skip) {
        return 0;
    }

    spdlog::info("context: {}", ctx.to_string());

    // now scan the folders under repo home and update the database

    // process the command on each repo, one thread per process

    return 0;
}
