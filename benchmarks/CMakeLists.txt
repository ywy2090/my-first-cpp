set(BENCHMARK_TARGET "benchmarks")
file(GLOB_RECURSE SRCS *.cpp)

# 测试程序
add_executable(${BENCHMARK_TARGET} ${SRCS})

get_target_property(BENCHMARK_LIB_DIR benchmark::benchmark IMPORTED_LOCATION)
get_target_property(BENCHMARK_INCLUDE_DIR benchmark::benchmark INTERFACE_INCLUDE_DIRECTORIES)

# Link Google Benchmark to the project
target_link_libraries(${BENCHMARK_TARGET} ${BENCHMARK_LIB_DIR})

# include dir
target_include_directories(${BENCHMARK_TARGET} PRIVATE ${BENCHMARK_INCLUDE_DIR})

add_dependencies(${BENCHMARK_TARGET} benchmark::benchmark)

# Link Shlwapi to the project
if("${CMAKE_SYSTEM_NAME}" MATCHES "Windows")
    target_link_libraries(${BENCHMARK_TARGET} Shlwapi)
endif()
