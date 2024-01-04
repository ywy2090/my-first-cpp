cmake_minimum_required(VERSION 3.14)

project(libtimewheel)

add_subdirectory(src)

if(TESTS)
    add_subdirectory(test)
endif(TESTS)