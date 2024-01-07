#include "Logger.h"

using namespace octo::logger;

void Logger::startLog(const std::string &logFile )
{
    if (m_running)
    {
        return;
    }

    m_running = true;

    log4cplus::PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT(logFile));

    logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("allLogger"));
    consoleLogger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("consoleLogger"));

    LOG_INFO("start log successfully");
}

void Logger::stopLog()
{
    LOG_INFO("try stop log");
    log4cplus::deinitialize();
}
