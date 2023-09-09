cmake_minimum_required(VERSION 3.10.0)

project(libmath)

add_subdirectory(src)

# unit test
if(TESTS)
    add_subdirectory(test)
endif(TESTS)

# benchmark
if(BENCHMARKS)
    add_subdirectory(benchmark)
endif(BENCHMARKS)