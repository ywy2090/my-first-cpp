include(ExternalProject)
ExternalProject_add(spdlog
    PREFIX ${THIRD_PARTY_DIR}
    DOWNLOAD_NAME spdlog-1.12.zip
    DOWNLOAD_NO_PROGRESS 1
    LOG_DOWNLOAD true
    LOG_BUILD true
    LOG_INSTALL true
    URL https://${URL_PREFIX}/gabime/spdlog/archive/refs/tags/v1.12.0.zip
    URL_HASH SHA256=6174bf8885287422a6c6a0312eb8a30e8d22bcfcee7c48a6d02d1835d7769232
    TLS_VERIFY false
    CMAKE_ARGS -DSPDLOG_BUILD_ALL=OFF
    -DBUILD_SHARED_LIBS=OFF
    -DCMAKE_BUILD_TYPE=Release
    -DSPDLOG_BUILD_SHARED=OFF
    -DCMAKE_INSTALL_PREFIX=${THIRD_PARTY_DIR}

    # INSTALL_COMMAND ""
    # INSTALL_DIR ${CMAKE_SOURCE_DIR}/deps/libs
)

file(MAKE_DIRECTORY ${THIRD_PARTY_INCLUDE_DIR})  # Must exist.
add_library(spdlog::spdlog INTERFACE IMPORTED GLOBAL)
# set_property(TARGET spdlog::spdlog PROPERTY IMPORTED_LOCATION ${THIRD_PARTY_LIBS_DIR}/${LIB_SPDLOG_TARGET}.a)
set_property(TARGET spdlog::spdlog PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${THIRD_PARTY_INCLUDE_DIR})

add_dependencies(spdlog::spdlog spdlog)