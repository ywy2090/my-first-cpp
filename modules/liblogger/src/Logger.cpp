#include "Logger.h"
#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include <spdlog/common.h>
#include <spdlog/spdlog.h>

using namespace octo::logger;

void Logger::startLog(const LogConf& logConf)
{
    if (m_running)
    {
        return;
    }

    m_running = true;

    std::string logPattern = "[%Y %H:%M:%S %f] [%l] [thread %t] [%s:%#] [%!]";
    auto rotateLogger = spdlog::rotating_logger_mt<spdlog::async_factory>("rotate_logger",
        logConf.logDir + "/" + logConf.logName, logConf.logFileSize, logConf.logFileCount);

    // auto dailyLogger = spdlog::daily_logger_mt<spdlog::async_factory>(
    //     "daily_logger", logConf.logDir + "/" + logConf.logName, 0, 0, logConf.logFileCount);

    rotateLogger->set_pattern(logPattern);
    rotateLogger->flush_on(spdlog::level::warn);
    rotateLogger->set_level(spdlog::level::from_str(logConf.logLevel));
    spdlog::set_default_logger(rotateLogger);

    m_spdlog = rotateLogger;

    spdlog::info("startLog successfully");
}

void Logger::stopLog()
{
    spdlog::drop_all();
}
