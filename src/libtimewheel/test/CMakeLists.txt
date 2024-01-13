set(TIMEWHEEL_TEST_TARGET "timewheel-test")
file(GLOB_RECURSE SRCS *.cpp)

# unit test excutable
add_executable(${TIMEWHEEL_TEST_TARGET} ${SRCS})

target_link_libraries(${TIMEWHEEL_TEST_TARGET} GTest::gtest_main ${TIME_WHEEL_TARGET})

# https://cmake.org/cmake/help/latest/command/add_test.html
add_test(NAME ${TIMEWHEEL_TEST_TARGET} COMMAND ${TIMEWHEEL_TEST_TARGET})

# include(GoogleTest)
# gtest_discover_tests(${TIMEWHEEL_TEST_TARGET})