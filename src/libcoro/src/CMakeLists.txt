cmake_minimum_required(VERSION 3.14)

# wildcard
# file(GLOB SRCS *.cpp)
# file(GLOB_RECURSE SRCS *.cpp)

set(CORO_GENERATOR_TARGET coro-generator-sample)
add_executable(${CORO_GENERATOR_TARGET} "CoroGenerator.cpp")

set(CPPCORO_GENERATOR_TARGET cppcoro-generator-sample)
add_executable(${CPPCORO_GENERATOR_TARGET} "CppCoroGenerator.cpp")
target_link_libraries(${CPPCORO_GENERATOR_TARGET} PRIVATE cppcoro::cppcoro)

# set(ASYNCIO_TARGET asyncio-sample)
# add_executable(${ASYNCIO_TARGET} "Asyncio.cpp")
# target_link_libraries(${ASYNCIO_TARGET} PRIVATE asyncio)

# add include directory
# target_include_directories(${CORO_GENERATOR_TARGET} PUBLIC .)
# add link libraries
# target_link_libraries(${CORO_GENERATOR_TARGET} PUBLIC jsoncpp_static OpenSSL::SSL OpenSSL::Crypto)