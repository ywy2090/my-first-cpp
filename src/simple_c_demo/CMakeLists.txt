cmake_minimum_required(VERSION 3.14)

project(simple-demo)

file(GLOB_RECURSE SRCS *.c)
set(SIMPLE_C_DEMO_TARGET simple-c-demo)

# test template program for c
add_executable(${SIMPLE_C_DEMO_TARGET} ${SRCS})

include(CheckCCompilerFlag)
include(CheckCXXCompilerFlag)

# check_cxx_compiler_flag(<flag> <resultVar>)
check_c_compiler_flag("-std=c99" resultVar)
if(resultVar)
    target_compile_options(${SIMPLE_C_DEMO_TARGET} PRIVATE -std=c99)  
endif(resultVar)


