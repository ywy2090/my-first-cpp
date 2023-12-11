cmake_minimum_required(VERSION 3.14)
project(leveldb-test)

file(GLOB_RECURSE SRCS *.cpp)

set(LEVELDB_TEST_TARGET leveldb-test)

# leveldb test
add_executable(${LEVELDB_TEST_TARGET} ${SRCS})

# target_compile_options(${LEVELDB_TEST_TARGET} PRIVATE -std=c99)

# Link Leveldb to the project
target_link_libraries(${LEVELDB_TEST_TARGET} ${MATH_TARGET} leveldb::leveldb)

# Include Directories
# target_include_directories(${LEVELDB_TEST_TARGET} PRIVATE ...)
add_dependencies(${LEVELDB_TEST_TARGET} leveldb::leveldb)