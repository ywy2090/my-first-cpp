#pragma once

#define LOG_MODULE(MODULE_NAME) "[" << MODULE_NAME << "]"
#define LOG_KV(KEY, VALUE) " ," << KEY << "=" << VALUE

#define LOG_TRACE(...)                                                     \
    do                                                                     \
    {                                                                      \
        auto& logger = octopus::logger::Logger::getInstance().getLogger(); \
        if (logger.isEnabledFor(log4cplus::TRACE_LOG_LEVEL))               \
        {                                                                  \
            LOG4CPLUS_TRACE(logger, __VA_ARGS__);                          \
        }                                                                  \
    } while (0)

#define LOG_DEBUG(...)                                                     \
    do                                                                     \
    {                                                                      \
        auto& logger = octopus::logger::Logger::getInstance().getLogger(); \
        if (logger.isEnabledFor(log4cplus::DEBUG_LOG_LEVEL))               \
        {                                                                  \
            LOG4CPLUS_DEBUG(logger, __VA_ARGS__);                          \
        }                                                                  \
    } while (0)

#define LOG_INFO(...)                                                      \
    do                                                                     \
    {                                                                      \
        auto& logger = octopus::logger::Logger::getInstance().getLogger(); \
        if (logger.isEnabledFor(log4cplus::INFO_LOG_LEVEL))                \
        {                                                                  \
            LOG4CPLUS_INFO(logger, __VA_ARGS__);                           \
        }                                                                  \
    } while (0)

#define LOG_WARN(...)                                                      \
    do                                                                     \
    {                                                                      \
        auto& logger = octopus::logger::Logger::getInstance().getLogger(); \
        if (logger.isEnabledFor(log4cplus::WARN_LOG_LEVEL))                \
        {                                                                  \
            LOG4CPLUS_WARN(logger, __VA_ARGS__);                           \
        }                                                                  \
    } while (0)

#define LOG_ERROR(...)                                                     \
    do                                                                     \
    {                                                                      \
        auto& logger = octopus::logger::Logger::getInstance().getLogger(); \
        if (logger.isEnabledFor(log4cplus::ERROR_LOG_LEVEL))               \
        {                                                                  \
            LOG4CPLUS_ERROR(logger, __VA_ARGS__);                          \
        }                                                                  \
    } while (0)

#define LOG_FATAL(...)                                                     \
    do                                                                     \
    {                                                                      \
        auto& logger = octopus::logger::Logger::getInstance().getLogger(); \
        if (logger.isEnabledFor(log4cplus::FATAL_LOG_LEVEL))               \
        {                                                                  \
            LOG4CPLUS_FATAL(logger, __VA_ARGS__);                          \
        }                                                                  \
    } while (0)

#define LOG_STD_TRACE(...)                                                        \
    do                                                                            \
    {                                                                             \
        auto& logger = octopus::logger::Logger::getInstance().getConsoleLogger(); \
        if (logger.isEnabledFor(log4cplus::TRACE_LOG_LEVEL))                      \
        {                                                                         \
            LOG4CPLUS_TRACE(logger, __VA_ARGS__);                                 \
        }                                                                         \
    } while (0)

#define LOG_STD_DEBUG(...)                                                        \
    do                                                                            \
    {                                                                             \
        auto& logger = octopus::logger::Logger::getInstance().getConsoleLogger(); \
        if (logger.isEnabledFor(log4cplus::DEBUG_LOG_LEVEL))                      \
        {                                                                         \
            LOG4CPLUS_DEBUG(logger, __VA_ARGS__);                                 \
        }                                                                         \
    } while (0)

#define LOG_STD_INFO(...)                                                         \
    do                                                                            \
    {                                                                             \
        auto& logger = octopus::logger::Logger::getInstance().getConsoleLogger(); \
        if (logger.isEnabledFor(log4cplus::INFO_LOG_LEVEL))                       \
        {                                                                         \
            LOG4CPLUS_INFO(logger, __VA_ARGS__);                                  \
        }                                                                         \
    } while (0)

#define LOG_STD_WARN(...)                                                         \
    do                                                                            \
    {                                                                             \
        auto& logger = octopus::logger::Logger::getInstance().getConsoleLogger(); \
        if (logger.isEnabledFor(log4cplus::WARN_LOG_LEVEL))                       \
        {                                                                         \
            LOG4CPLUS_WARN(logger, __VA_ARGS__);                                  \
        }                                                                         \
    } while (0)

#define LOG_STD_ERROR(...)                                                        \
    do                                                                            \
    {                                                                             \
        auto& logger = octopus::logger::Logger::getInstance().getConsoleLogger(); \
        if (logger.isEnabledFor(log4cplus::ERROR_LOG_LEVEL))                      \
        {                                                                         \
            LOG4CPLUS_ERROR(logger, __VA_ARGS__);                                 \
        }                                                                         \
    } while (0)

#define LOG_STD_FATAL(...)                                                        \
    do                                                                            \
    {                                                                             \
        auto& logger = octopus::logger::Logger::getInstance().getConsoleLogger(); \
        if (logger.isEnabledFor(log4cplus::FATAL_LOG_LEVEL))                      \
        {                                                                         \
            LOG4CPLUS_FATAL(logger, __VA_ARGS__);                                 \
        }                                                                         \
    } while (0)
