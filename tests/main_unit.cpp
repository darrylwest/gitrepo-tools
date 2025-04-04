//
// Created by Darryl West on 3/22/25.
//
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() function

#include <catch2/catch_all.hpp>
#include <gitrepo/version.hpp>
#include <vendor/ansi_colors.hpp>
#include <spdlog/spdlog.h>
#include <print>
#include <vendor/perftimer.hpp>

perftimer::PerfTimer timer("Catch2 Unit Tests");

struct MainTestSetup {

    MainTestSetup() {
        using namespace colors;
        spdlog::set_level(spdlog::level::critical);

        // do any config stuff
        timer.start();
    }

    ~MainTestSetup() {
        using namespace colors;
        timer.stop();
        const auto version = gitrepo::Version();
        std::println("{}Tests complete, version: {}", bright::cyan, version.to_string());
        timer.show_duration(": ");
        std::puts(colors::reset.c_str());
    }
};

// put helpers here...
MainTestSetup setup;

