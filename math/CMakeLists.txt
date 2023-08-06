cmake_minimum_required(VERSION 3.10.0)

project(math)

add_subdirectory(src)

# 单元测试
if(TESTS)
    add_subdirectory(test)
endif(TESTS)

# 基准测试
if(BENCHMARKS)
    add_subdirectory(benchmark)
endif(BENCHMARKS)