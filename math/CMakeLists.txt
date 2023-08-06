cmake_minimum_required(VERSION 3.20.0)

project(math)

add_subdirectory(src)

include_directories()

# 单元测试
if(TESTS)
    add_subdirectory(test)
endif(TESTS)

# 基准测试
if(BENCH_MARK)
    add_subdirectory(benchmark)
endif(BENCH_MARK)