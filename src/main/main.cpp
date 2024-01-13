
#include "Common.h"
#include "liblogger/src/Logger.h"
#include "libtimewheel/src/HashedTimeWheelTimer.h"
#include "usage.h"
#include <cstring>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>

int main(int argc, char* argv[])
{
    if (argc >= 2 && ((0 == strncmp(argv[1], "-v", 2) || 0 == strncmp(argv[1], "--version", 8))))
    {
        initializer::printVersion();
        return 0;
    }

    {
        nlohmann::json j = R"({ "happy": true, "pi": 3.141 })";
        std::string jsonString = j.dump();
        std::cout << "json => " << jsonString << std::endl;
        // Rest of your code...
    }

    // start log
    octopus::logger::Logger::getInstance().startLog();

    // start timewheel timer
    auto timewheel = std::make_shared<octopus::timewheel::HashedTimeWheelTimer>();
    timewheel->start();

    LOG_INFO("start main ");

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}