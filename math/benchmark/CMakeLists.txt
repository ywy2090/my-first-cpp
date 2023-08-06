cmake_minimum_required(VERSION 3.10)

set(BENCHMARK_ENABLE_TESTING NO)

include(FetchContent)
FetchContent_Declare(
    googlebenchmark
    URL https://codeload.github.com/google/benchmark/zip/refs/tags/v1.8.2
)
FetchContent_MakeAvailable(googlebenchmark)

set(MATH_BENCHMARK_TARGET "math-benchmark")
file(GLOB_RECURSE SRCS *.cpp)

# 测试程序
add_executable(${MATH_BENCHMARK_TARGET} ${SRCS})

# Link Google Benchmark to the project
target_link_libraries(${MATH_BENCHMARK_TARGET} ${MATH_TARGET} benchmark::benchmark)

# Link Shlwapi to the project
if ("${CMAKE_SYSTEM_NAME}" MATCHES "Windows")
    target_link_libraries(${MATH_BENCHMARK_TARGET} Shlwapi)
endif()