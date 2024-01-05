include(ExternalProject)
ExternalProject_add(cppcoro
    PREFIX ${THIRD_PARTY_DIR}
    DOWNLOAD_NAME cppcoro-e86216e4.zip
    DOWNLOAD_NO_PROGRESS 1
    LOG_DOWNLOAD true
    LOG_BUILD true
    LOG_INSTALL true

    # TODO: modify url
    URL https://codeload.github.com/andreasbuhr/cppcoro/zip/e86216e4fa6145f0184b5fef79230e9d4dc3aa77
    URL_HASH SHA256=5f67a8d586479f76961424e16b5cd8cd7a328fd14ac0d27f3d0551896e25a084
    TLS_VERIFY false
    CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF
    -DCMAKE_BUILD_TYPE=Release
    -DBUILD_TESTING=OFF
    -DCMAKE_INSTALL_PREFIX=${THIRD_PARTY_DIR}
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

    # INSTALL_COMMAND ""
    # INSTALL_DIR ${CMAKE_SOURCE_DIR}/deps/libs
)

file(MAKE_DIRECTORY ${THIRD_PARTY_INCLUDE_DIR}) # Must exist.
add_library(cppcoro::cppcoro STATIC IMPORTED GLOBAL)
set_property(TARGET cppcoro::cppcoro PROPERTY IMPORTED_LOCATION ${THIRD_PARTY_LIBS_DIR}/libcppcoro.a)
set_property(TARGET cppcoro::cppcoro PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${THIRD_PARTY_INCLUDE_DIR})

add_dependencies(cppcoro::cppcoro cppcoro)