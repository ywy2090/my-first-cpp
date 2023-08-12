cmake_minimum_required(VERSION 3.10)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(MATH_TEST_TARGET "math-test")
file(GLOB_RECURSE SRCS *.cpp)

# 测试程序
add_executable(${MATH_TEST_TARGET} ${SRCS})

# TODO: 如何安装的库的头/lib文件，其他模块inlude link
target_link_libraries(${MATH_TEST_TARGET} GTest::gtest_main ${MATH_TARGET})

include(GoogleTest)
gtest_discover_tests(${MATH_TEST_TARGET})