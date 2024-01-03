cmake_minimum_required(VERSION 3.14)

set(MATH_TEST_TARGET "math-test")
file(GLOB_RECURSE SRCS *.cpp)

# math unit test executable
add_executable(${MATH_TEST_TARGET} ${SRCS})

target_link_libraries(${MATH_TEST_TARGET} GTest::gtest_main ${MATH_TARGET})

# include(GoogleTest)
# gtest_discover_tests(${MATH_TEST_TARGET})