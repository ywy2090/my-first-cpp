cmake_minimum_required(VERSION 3.14)

# wildcard *.cpp files
# file(GLOB SRCS *.cpp)
file(GLOB_RECURSE SRCS *.cpp)

add_library(${LOGGER_TARGET} ${SRCS})

# add include directory
target_include_directories(${LOGGER_TARGET} PUBLIC .)

find_package(log4cplus REQUIRED)

# link libraris for main excutable
target_link_libraries(${LOGGER_TARGET} PUBLIC log4cplus::log4cplus)

# install library
# install(TARGETS ${LOGGER_TARGET} EXPORT mathTargets ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}")
install(TARGETS ${LOGGER_TARGET} ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}")
# install head files
install(DIRECTORY ${LOGGER_TARGET} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/" FILES_MATCHING PATTERN "*.h")