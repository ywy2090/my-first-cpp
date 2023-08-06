cmake_minimum_required(VERSION 3.20.0)

project(math)

message(STATUS "CMakeLists.txt for math")

add_subdirectory(src)

include_directories()

# ut
if(TESTS)
    add_subdirectory(test)
endif(TESTS)

# 基准测试
if(BENCH_MARK)
    add_subdirectory(benchmark)
endif(BENCH_MARK)