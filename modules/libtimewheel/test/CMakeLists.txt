set(TIMEWHEEL_TEST_TARGET "timewheel-test")
file(GLOB_RECURSE SRCS *.cpp)

# unit test excutable
add_executable(${TIMEWHEEL_TEST_TARGET} ${SRCS})

target_link_libraries(${TIMEWHEEL_TEST_TARGET} GTest::gtest_main timewheel)

# include(GoogleTest)
# gtest_discover_tests(${TIMEWHEEL_TEST_TARGET})