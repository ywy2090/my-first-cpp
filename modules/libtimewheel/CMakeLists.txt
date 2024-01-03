cmake_minimum_required(VERSION 3.14)

project(libtimewheel)

add_subdirectory(src)
add_subdirectory(test)

if(TESTS AND EXISTS test)
    add_subdirectory(test)
endif(TESTS AND EXISTS test)