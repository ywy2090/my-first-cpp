#pragma once

#define LOG_TRACE(...)  do { \
    auto &logger = octo::logger::Logger::getInstance().getLogger(); \
    LOG4CPLUS_TRACE(logger, __VA_ARGS__); \
} while(0)

#define LOG_DEBUG(...)  do { \
    auto &logger = octo::logger::Logger::getInstance().getLogger(); \
    LOG4CPLUS_DEBUG(logger, __VA_ARGS__); \
} while(0)

#define LOG_INFO(...)  do { \
    auto &logger = octo::logger::Logger::getInstance().getLogger(); \
    LOG4CPLUS_INFO(logger, __VA_ARGS__); \
} while(0)

#define LOG_WARN(...)  do { \
    auto &logger = octo::logger::Logger::getInstance().getLogger(); \
    LOG4CPLUS_WARN(logger, __VA_ARGS__); \
} while(0)

#define LOG_ERROR(...)  do { \
    auto &logger = octo::logger::Logger::getInstance().getLogger(); \
    LOG4CPLUS_ERROR(logger, __VA_ARGS__); \
} while(0)

#define LOG_FATAL(...)  do { \
    auto &logger = octo::logger::Logger::getInstance().getLogger(); \
    LOG4CPLUS_FATAL(logger, __VA_ARGS__); \
} while(0)

#define LOG_STD_TRACE(...)  do { \
    auto &logger = octo::logger::Logger::getInstance().getConsoleLogger(); \
    LOG4CPLUS_TRACE(logger, __VA_ARGS__); \
} while(0)

#define LOG_STD_DEBUG(...)  do { \
    auto &logger = octo::logger::Logger::getInstance().getConsoleLogger(); \
    LOG4CPLUS_DEBUG(logger, __VA_ARGS__); \
} while(0)

#define LOG_STD_INFO(...)  do { \
    auto &logger = octo::logger::Logger::getInstance().getConsoleLogger(); \
    LOG4CPLUS_INFO(logger, __VA_ARGS__); \
} while(0)

#define LOG_STD_WARN(...)  do { \
    auto &logger = octo::logger::Logger::getInstance().getConsoleLogger(); \
    LOG4CPLUS_WARN(logger, __VA_ARGS__); \
} while(0)

#define LOG_STD_ERROR(...)  do { \
    auto &logger = octo::logger::Logger::getInstance().getConsoleLogger(); \
    LOG4CPLUS_ERROR(logger, __VA_ARGS__); \
} while(0)

#define LOG_STD_FATAL(...)  do { \
    auto &logger = octo::logger::Logger::getInstance().getConsoleLogger(); \
    LOG4CPLUS_FATAL(logger, __VA_ARGS__); \
} while(0)
