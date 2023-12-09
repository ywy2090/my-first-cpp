#pragma once
#include "Common.h"
#include "spdlog/spdlog.h"
#include <algorithm>
#include <atomic>
#include <memory>

namespace octo
{
namespace logger
{

struct LogConf
{
    std::string logName = "demo.log";
    std::string logDir = "./logs";

    std::string logLevel = "info";
    int logFileSize = 1024 * 1024 * 200;
    int logFileCount = 10;
};

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
    std::shared_ptr<spdlog::logger> spdlog() const { return m_spdlog; }

    static Logger& getInstance()
    {
        static Logger logger;
        return logger;
    }

    // start log
    virtual void startLog(const LogConf& logConf = LogConf{});
    virtual void stopLog();

private:
    std::atomic<bool> m_running{false};
    std::shared_ptr<spdlog::logger> m_spdlog;
};
}  // namespace logger
}  // namespace octo
