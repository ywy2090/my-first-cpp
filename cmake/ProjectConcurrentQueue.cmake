include(ExternalProject)
ExternalProject_add(concurrentqueue
    PREFIX ${THIRD_PARTY_DIR}
    DOWNLOAD_NAME concurrentqueue-1.0.4.zip
    DOWNLOAD_NO_PROGRESS 1
    LOG_DOWNLOAD true
    LOG_BUILD true
    LOG_INSTALL true
    URL https://github.com/cameron314/concurrentqueue/archive/refs/tags/v1.0.4.zip
    URL_HASH SHA256=6874cb028c27bf0d00ebdb3784c65e0aae004f9ad287301708aa9d8b836be57a
    TLS_VERIFY false
    CMAKE_ARGS
    -DBUILD_SHARED_LIBS=OFF
    -DCMAKE_BUILD_TYPE=Release
    -DCMAKE_INSTALL_PREFIX=${THIRD_PARTY_DIR}

    # INSTALL_COMMAND ""
    # INSTALL_DIR ${CMAKE_SOURCE_DIR}/deps/libs
)

file(MAKE_DIRECTORY ${THIRD_PARTY_INCLUDE_DIR})  # Must exist.
add_library(${LIB_CONCURRENTQUQUE_TARGET} STATIC IMPORTED GLOBAL)
# set_property(TARGET ${LIB_CONCURRENTQUQUE_TARGET} PROPERTY IMPORTED_LOCATION ${THIRD_PARTY_LIBS_DIR}/${LIB_CONCURRENTQUQUE_TARGET}.a)
set_property(TARGET ${LIB_CONCURRENTQUQUE_TARGET} PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${THIRD_PARTY_INCLUDE_DIR})

add_dependencies(${LIB_CONCURRENTQUQUE_TARGET} concurrentqueue)