cmake_minimum_required(VERSION 3.14)

# wildcard
# file(GLOB SRCS *.cpp)
# file(GLOB_RECURSE SRCS *.cpp)

set(CORO_GENERATOR_TARGET coro-generator-sample)
add_executable(${CORO_GENERATOR_TARGET} "CoroGenerator.cpp")

# add include directory
# target_include_directories(${CORO_GENERATOR_TARGET} PUBLIC .)
# add link libraries
# target_link_libraries(${CORO_GENERATOR_TARGET} PUBLIC jsoncpp_static OpenSSL::SSL OpenSSL::Crypto)