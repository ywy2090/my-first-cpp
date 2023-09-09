cmake_minimum_required(VERSION 3.14)

# wildcard *.cpp files
# file(GLOB SRCS *.cpp)
file(GLOB_RECURSE SRCS *.cpp)

add_library(${LOGGER_TARGET} ${SRCS})

# add include directory
target_include_directories(${LOGGER_TARGET} PUBLIC .)

# link libraris for main excutable
target_link_libraries(${LOGGER_TARGET} PUBLIC ${LIB_SPDLOG_TARGET})

add_dependencies(${LOGGER_TARGET} ${LIB_SPDLOG_TARGET})

# install library
# install(TARGETS ${LOGGER_TARGET} EXPORT mathTargets ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}")
install(TARGETS ${LOGGER_TARGET} ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}")
# install head files
install(DIRECTORY ${LOGGER_TARGET} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/" FILES_MATCHING PATTERN "*.h")