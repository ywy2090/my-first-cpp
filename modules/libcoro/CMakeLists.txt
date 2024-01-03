cmake_minimum_required(VERSION 3.14)

project(libcoro)

add_subdirectory(src)

# unit test
if(TESTS AND EXISTS test)
    add_subdirectory(test)
endif(TESTS AND EXISTS test)

# benchmark
if(BENCHMARKS AND EXISTS benchmark)
    add_subdirectory(benchmark)
endif(BENCHMARKS AND EXISTS benchmark)