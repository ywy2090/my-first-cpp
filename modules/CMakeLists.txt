cmake_minimum_required(VERSION 3.10.0)

project(modules)

option(USE_LIBMATH "Use tutorial provided math implementation" ON)

if(USE_LIBMATH)
    # 加载my_math模块
    add_subdirectory(libmath)
endif(USE_LIBMATH)

add_subdirectory(simple_c_demo)
add_subdirectory(leveldb_test)
# TODO: 添加其他模块