include(ExternalProject)
ExternalProject_add(async-simple
    PREFIX ${THIRD_PARTY_DIR}
    DOWNLOAD_NAME async-simple-1.2.tar.gz
    DOWNLOAD_NO_PROGRESS 1
    LOG_DOWNLOAD true
    LOG_BUILD true
    LOG_INSTALL true
    LOG_CONFIGURE true
    LOG_BUILD true
    URL https://${URL_PREFIX}/alibaba/async_simple/archive/refs/tags/1.2.zip
    URL_HASH SHA256=0c39ec74712b2ed1029258ce1c285fec39eeab4460dff1c80717ca279268b14c
    CMAKE_ARGS -DASYNC_SIMPLE_ENABLE_TESTS=OFF 
    -DASYNC_SIMPLE_BUILD_DEMO_EXAMPLE=OFF
    -DCMAKE_INSTALL_PREFIX=${THIRD_PARTY_DIR}

    # INSTALL_COMMAND ""
    # INSTALL_DIR ${CMAKE_SOURCE_DIR}/deps/libs
)

file(MAKE_DIRECTORY ${THIRD_PARTY_INCLUDE_DIR})  # Must exist.
add_library(async_simple::async_simple STATIC IMPORTED GLOBAL)
set_property(TARGET async_simple::async_simple PROPERTY IMPORTED_LOCATION ${THIRD_PARTY_LIBS_DIR}/libasync_simple.a)
set_property(TARGET async_simple::async_simple PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${THIRD_PARTY_INCLUDE_DIR})

add_dependencies(async_simple::async_simple async_simple)