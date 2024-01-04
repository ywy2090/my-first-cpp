cmake_minimum_required(VERSION 3.14)

project(modules)

# option(USE_LIBMATH "Use tutorial provided math implementation" ON)

add_subdirectory(libtimewheel)

add_subdirectory(liblogger)
add_subdirectory(libcoro)
add_subdirectory(simple_c_demo)
add_subdirectory(leveldb_demo)
# TODO: add more modules