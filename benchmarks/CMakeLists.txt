set(BENCHMARK_TARGET "benchmarks")
file(GLOB_RECURSE SRCS *.cpp)

# concurrentqueue
find_package(unofficial-concurrentqueue CONFIG REQUIRED)

# Test Executable
add_executable(${BENCHMARK_TARGET} ${SRCS})

# Link Google Benchmark to the project
target_link_libraries(${BENCHMARK_TARGET} benchmark::benchmark jsoncpp_lib nlohmann::json unofficial::concurrentqueue::concurrentqueue)


# Include Directories
target_include_directories(${BENCHMARK_TARGET} PRIVATE ${READERWRITERQUEUE_INCLUDE_DIRS})

# Link Shlwapi to the project
if("${CMAKE_SYSTEM_NAME}" MATCHES "Windows")
    target_link_libraries(${BENCHMARK_TARGET} Shlwapi)
endif()

add_dependencies(${BENCHMARK_TARGET} benchmark::benchmark jsoncpp_lib nlohmann::json)
