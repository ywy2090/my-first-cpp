cmake_minimum_required(VERSION 3.10.0)

project(leveldb-test)

file(GLOB_RECURSE SRCS *.cpp)

set(LEVELDB_TEST_TARGET leveldb-test)

get_target_property(LEVELDB_LIB_DIR ${LIB_LEVELDB_TARGET} IMPORTED_LOCATION)
get_target_property(LEVELDB_INCLUDE_DIR ${LIB_LEVELDB_TARGET} INTERFACE_INCLUDE_DIRECTORIES)

# leveldb test
add_executable(${LEVELDB_TEST_TARGET} ${SRCS})
# target_compile_options(${LEVELDB_TEST_TARGET} PRIVATE -std=c99)

# Link Leveldb to the project
target_link_libraries(${LEVELDB_TEST_TARGET} ${MATH_TARGET} ${LEVELDB_LIB_DIR})

# include dir
target_include_directories(${LEVELDB_TEST_TARGET} PRIVATE ${LEVELDB_INCLUDE_DIR})

add_dependencies(${LEVELDB_TEST_TARGET} ${LIB_LEVELDB_TARGET})