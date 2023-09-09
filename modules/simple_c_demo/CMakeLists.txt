cmake_minimum_required(VERSION 3.14)

project(simple-demo)

file(GLOB_RECURSE SRCS *.c)

set(SIMPLE_C_DEMO_TARGET simple-c-demo)

# 测试程序
add_executable(${SIMPLE_C_DEMO_TARGET} ${SRCS})
target_compile_options(${SIMPLE_C_DEMO_TARGET} PRIVATE -std=c99)