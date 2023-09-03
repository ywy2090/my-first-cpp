set(MATH_BENCHMARK_TARGET "math-benchmark")
file(GLOB_RECURSE SRCS *.cpp)

# 测试程序
add_executable(${MATH_BENCHMARK_TARGET} ${SRCS})


get_target_property(BENCHMARK_LIB_DIR libbenchmark IMPORTED_LOCATION)
get_target_property(BENCHMARK_INCLUDE_DIR libbenchmark INTERFACE_INCLUDE_DIRECTORIES)

# Link Google Benchmark to the project
target_link_libraries(${MATH_BENCHMARK_TARGET} ${MATH_TARGET} ${BENCHMARK_LIB_DIR})
# include dir
target_include_directories(${MATH_BENCHMARK_TARGET} PRIVATE ${BENCHMARK_INCLUDE_DIR})

# Link Shlwapi to the project
if ("${CMAKE_SYSTEM_NAME}" MATCHES "Windows")
    target_link_libraries(${MATH_BENCHMARK_TARGET} Shlwapi)
endif()

