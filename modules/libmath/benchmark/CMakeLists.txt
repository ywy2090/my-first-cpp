set(MATH_BENCHMARK_TARGET "math-benchmark")
file(GLOB_RECURSE SRCS *.cpp)

# test target
add_executable(${MATH_BENCHMARK_TARGET} ${SRCS})

# Link Google Benchmark to the project
target_link_libraries(${MATH_BENCHMARK_TARGET} ${MATH_TARGET} benchmark::benchmark)

# Include Directories
# target_include_directories(${MATH_BENCHMARK_TARGET} PRIVATE ...)

# Link Shlwapi to the project
if("${CMAKE_SYSTEM_NAME}" MATCHES "Windows")
    target_link_libraries(${MATH_BENCHMARK_TARGET} Shlwapi)
endif()

add_dependencies(${MATH_BENCHMARK_TARGET} benchmark::benchmark)
