//
// Created by Darryl West on 3/22/25.
//
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() function

#include <catch2/catch_all.hpp>
#include <gitrepo/tools.hpp>
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
        std::println("{}Tests complete...{}", bright::cyan, colors::reset);
        timer.show_duration();
    }
};

// put helpers here...
MainTestSetup setup;

