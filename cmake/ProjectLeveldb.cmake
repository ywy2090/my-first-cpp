include(ExternalProject)
ExternalProject_add(leveldb
    PREFIX ${THIRD_PARTY_DIR}
    DOWNLOAD_NAME leveldb-1.23.tar.gz
    DOWNLOAD_NO_PROGRESS 1
    LOG_DOWNLOAD true
    LOG_BUILD true 
    LOG_INSTALL true 
    URL https://github.com/google/leveldb/archive/refs/tags/1.23.zip
    URL_HASH SHA256=a6fa7eebd11de709c46bf1501600ed98bf95439d6967963606cc964931ce906f
    CMAKE_ARGS -DLEVELDB_BUILD_TESTS=OFF 
        -DBUILD_SHARED_LIBS=OFF
        -DCMAKE_BUILD_TYPE=Release 
        -DLEVELDB_BUILD_BENCHMARKS=OFF
        -DCMAKE_INSTALL_PREFIX=${THIRD_PARTY_DIR} 
    # INSTALL_COMMAND ""
    # INSTALL_DIR ${CMAKE_SOURCE_DIR}/deps/libs
    )

#file(MAKE_DIRECTORY ${THIRD_PARTY_INCLUDE_DIR})  # Must exist.

add_library(libleveldb STATIC IMPORTED GLOBAL)
set_property(TARGET libleveldb PROPERTY IMPORTED_LOCATION ${THIRD_PARTY_LIBS_DIR}/libleveldb.a)
set_property(TARGET libleveldb PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${THIRD_PARTY_INCLUDE_DIR})

add_dependencies(libleveldb leveldb)