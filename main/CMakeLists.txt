cmake_minimum_required(VERSION 3.1.0)

# file(GLOB SRCS *.cpp) # wildcard all x.cpp files of the current dir
file(GLOB_RECURSE SRCS *.cpp) # recurse wildcard all x.cpp files of the current dir

# find deps by find_package
# find_package(fmt REQUIRED)
# find_package(range-v3 REQUIRED)
# find_package(cxxopts REQUIRED)

# executable file
add_executable(${PROJECT_NAME} ${SRCS})

add_compile_definitions(SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE)

# link libraris for main excutable
target_link_libraries(${PROJECT_NAME} PRIVATE ${MATH_TARGET} ${LOGGER_TARGET})