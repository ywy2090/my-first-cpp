#include "BuildInfo.h"
#include "Common.h"
#include "Logger.h"
#include "MyMath.h"
#include <cstring>
#include <iostream>

void printVersion()
{
    std::cout << "Project Version    : " << PROJECT_PROJECT_VERSION << std::endl;
    std::cout << "Build Time         : " << PROJECT_BUILD_TIME << std::endl;
    std::cout << "Build Type         : " << PROJECT_BUILD_PLATFORM << "/" << PROJECT_BUILD_TYPE
              << std::endl;
    std::cout << "Git Branch         : " << PROJECT_BUILD_BRANCH << std::endl;
    std::cout << "Git Commit         : " << PROJECT_COMMIT_HASH << std::endl;
}

/*
#include <fmt/format.h>
#include <cxxopts.hpp>

#include <range/v3/view.hpp>

namespace view = ranges::views;

int fib(int x)
{
    int a = 0, b = 1;

    for (int it : view::repeat(0) | view::take(x))
    {
        (void)it;
        int tmp = a;
        a += b;
        b = tmp;
    }

    return a;
}

int main0(int argc, char** argv)
{
    cxxopts::Options options("fibo", "Print the fibonacci sequence up to a value 'n'");
    options.add_options()(
        "n,value", "The value to print to", cxxopts::value<int>()->default_value("10"));

    auto result = options.parse(argc, argv);
    auto n = result["value"].as<int>();

    for (int x : view::iota(1) | view::take(n))
    {
        fmt::print("fib({}) = {}\n", x, fib(x));
    }
}
*/

int main(int argc, char* argv[])
{
    if (argc >= 2 && ((0 == strncmp(argv[1], "-v", 2) || 0 == strncmp(argv[1], "--version", 8))))
    {
        printVersion();
        return 0;
    }

    // {
    //     math::Math math;
    //     std::cout << "1 + 2 = " << math.add(1, 2) << std::endl;
    // }

    // start log
    auto& logger = octo::logger::Logger::getInstance();
    logger.startLog();

    LOG_INFO("Welcome to spdlog!");
    LOG_ERROR("Some error message with arg: {}", 1);

    LOG_WARN("Easy padding in numbers like {:08d}", 12);

    LOG_INFO("Support for floats {:03.2f}", 1.23456);
    LOG_INFO("Positional args are {1} {0}..", "too", "supported");
    LOG_INFO("{:<30}", "left aligned");

    spdlog::set_level(spdlog::level::debug);  // Set global log level to debug
    LOG_DEBUG("This message should be displayed..");

    // Compile time log levels
    // define SPDLOG_ACTIVE_LEVEL to desired level
    LOG_TRACE("Some trace message with param {}", 42);
    LOG_DEBUG("Some debug message");
    LOG_CRITICAL("Some debug message");

    return 0;
}