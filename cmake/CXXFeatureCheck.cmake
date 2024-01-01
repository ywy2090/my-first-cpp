
# Check for C/C++ support features

include(CheckCSourceRuns)
include(CheckCXXSourceRuns)

# c++20 std::format
FILE(READ "${CMAKE_SOURCE_DIR}/cmake/templates/cxx20_format.cpp" CXX20_FORMAT_TEST)
check_cxx_source_runs("${CXX20_FORMAT_TEST}" CXX20_FORMAT_TEST_RESULT)
message(STATUS "Checking for C++20 std::format support: ${CXX20_FORMAT_TEST_RESULT}")
unset(CXX20_FORMAT_TEST_RESULT)

# c++20 coroutine
FILE(READ "${CMAKE_SOURCE_DIR}/cmake/templates/cxx20_coro.cpp" CXX20_CORO_TEST)
check_cxx_source_runs("${CXX20_CORO_TEST}" CXX20_CORO_TEST_RESULT)
message(STATUS "Checking for C++20 coroutine support: ${CXX20_CORO_TEST_RESULT}")
unset(CXX20_CORO_TEST_RESULT)