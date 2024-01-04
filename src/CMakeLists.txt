# option(USE_LIBMATH "Use tutorial provided math implementation" ON)

# main program
add_subdirectory(main)
add_subdirectory(libtimewheel)

add_subdirectory(liblogger)
add_subdirectory(libcoro)
add_subdirectory(simple_c_demo)
add_subdirectory(leveldb_demo)
# TODO: add more modules