include(ExternalProject)
ExternalProject_add(json-cpp
    PREFIX ${THIRD_PARTY_DIR}
    DOWNLOAD_NAME json-cpp-v1.9.5.zip
    DOWNLOAD_NO_PROGRESS 1
    LOG_DOWNLOAD true
    LOG_BUILD true
    LOG_INSTALL true
    URL https://github.com/open-source-parsers/jsoncpp/archive/refs/tags/1.9.5.zip
    URL_HASH SHA256=a074e1b38083484e8e07789fd683599d19da8bb960959c83751cd0284bdf2043
    TLS_VERIFY false
    CMAKE_ARGS -DJSONCPP_WITH_TESTS=OFF
    -DJSONCPP_WITH_POST_BUILD_UNITTEST=OFF
    -DJSONCPP_WITH_EXAMPLE=OFF
    -DBUILD_SHARED_LIBS=OFF
    -DCMAKE_BUILD_TYPE=Release
    -DCMAKE_INSTALL_PREFIX=${THIRD_PARTY_DIR}

    # INSTALL_COMMAND ""
    # INSTALL_DIR ${CMAKE_SOURCE_DIR}/deps/libs
)

# nlohmann_json::nlohmann_json
file(MAKE_DIRECTORY ${THIRD_PARTY_INCLUDE_DIR})  # Must exist.
add_library(jsoncpp_lib STATIC IMPORTED GLOBAL)

set_property(TARGET jsoncpp_lib PROPERTY IMPORTED_LOCATION ${THIRD_PARTY_LIBS_DIR}/libjsoncpp.a)
set_property(TARGET jsoncpp_lib PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${THIRD_PARTY_INCLUDE_DIR})

add_dependencies(jsoncpp_lib json-cpp)