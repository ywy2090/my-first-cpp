cmake_minimum_required(VERSION 3.14)

project(libtimewheel)

add_subdirectory(src)

if(TESTS AND EXISTS test)
    add_subdirectory(test)
endif(TESTS AND EXISTS test)