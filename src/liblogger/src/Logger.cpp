#include "Logger.h"

using namespace octopus::logger;

void Logger::startLog(const std::string& logFile)
{
    if (m_running)
    {
        return;
    }

    m_running = true;

    log4cplus::PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT(logFile));

    logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("allLogger"));
    consoleLogger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("consoleLogger"));

    LOG_INFO("start logger successfully");
}

void Logger::stopLog()
{
    LOG_INFO("try stop logger");
    log4cplus::deinitialize();
}
