#pragma once
#include "Common.h"
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/stringhelper.h>
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <algorithm>
#include <atomic>

namespace octopus
{
namespace logger
{

class Logger
{
public:
    Logger() = default;
    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger&& operator=(Logger&&) = delete;

    virtual ~Logger() noexcept { this->stopLog(); }

public:
    static Logger& getInstance()
    {
        static Logger logger;
        return logger;
    }

    /**
     * @brief start logger
     *
     * @param logFile log configuration file, default: log.properties
     */
    virtual void startLog(const std::string& logFile = "log.properties");
    /**
     * @brief stop logger
     */
    virtual void stopLog();

    inline const log4cplus::Logger& getLogger() const { return logger; }
    inline const log4cplus::Logger& getConsoleLogger() const { return consoleLogger; }

private:
    std::atomic<bool> m_running{false};

    log4cplus::Logger logger;
    log4cplus::Logger consoleLogger;
};
}  // namespace logger
}  // namespace octopus
