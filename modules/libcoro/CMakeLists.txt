cmake_minimum_required(VERSION 3.14)

project(libcoro)

add_subdirectory(src)

# unit test
if(TESTS)
    add_subdirectory(test)
endif(TESTS)

# benchmark
if(BENCHMARKS AND EXISTS benchmark)
    add_subdirectory(benchmark)
endif(BENCHMARKS)