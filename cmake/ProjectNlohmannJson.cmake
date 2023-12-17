include(ExternalProject)
ExternalProject_add(nlohmann-json
    PREFIX ${THIRD_PARTY_DIR}
    DOWNLOAD_NAME nlohmann-json-v3.11.3.zip
    DOWNLOAD_NO_PROGRESS 1
    LOG_DOWNLOAD true
    LOG_BUILD true
    LOG_INSTALL true
    URL https://${URL_PREFIX}/nlohmann/json/archive/refs/tags/v3.11.3.zip
    URL_HASH SHA256=04022b05d806eb5ff73023c280b68697d12b93e1b7267a0b22a1a39ec7578069
    TLS_VERIFY false
    CMAKE_ARGS -DJSON_BuildTests=OFF
    -DBUILD_SHARED_LIBS=OFF
    -DCMAKE_BUILD_TYPE=Release
    -DCMAKE_INSTALL_PREFIX=${THIRD_PARTY_DIR}

    # INSTALL_COMMAND ""
    # INSTALL_DIR ${CMAKE_SOURCE_DIR}/deps/libs
)

# nlohmann_json::nlohmann_json
file(MAKE_DIRECTORY ${THIRD_PARTY_INCLUDE_DIR})  # Must exist.
add_library(nlohmann::json INTERFACE IMPORTED GLOBAL)
# head only
# set_property(TARGET nlohmann::json PROPERTY IMPORTED_LOCATION ${THIRD_PARTY_LIBS_DIR}/${LIB_JSON_TARGET}.a)
set_property(TARGET nlohmann::json PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${THIRD_PARTY_INCLUDE_DIR})

add_dependencies(nlohmann::json nlohmann-json)