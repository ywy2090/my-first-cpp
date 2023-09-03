# set(BENCHMARK_ENABLE_TESTING NO)
# include(FetchContent)
# FetchContent_Declare(
#     googlebenchmark
#     URL https://codeload.github.com/google/benchmark/zip/refs/tags/v1.8.2
# )
# FetchContent_MakeAvailable(googlebenchmark)

include(ExternalProject)
ExternalProject_add(googlebenchmark
    PREFIX ${THIRD_PARTY_DIR}
    DOWNLOAD_NAME googlebenchmark-1.8.2.tar.gz
    DOWNLOAD_NO_PROGRESS 1
    LOG_DOWNLOAD true
    LOG_BUILD true 
    LOG_INSTALL true 
    URL https://codeload.github.com/google/benchmark/zip/refs/tags/v1.8.2
    URL_HASH SHA256=0094b77c01e9973876f1831f76cbae43fdaf09b424e467dc4171abaa6884e455
    CMAKE_ARGS -DBENCHMARK_ENABLE_TESTING=OFF 
        -DCMAKE_INSTALL_PREFIX=${THIRD_PARTY_DIR} 
        -DCMAKE_BUILD_TYPE=Release 
        -DBENCHMARK_ENABLE_GTEST_TESTS=OFF 
        -DBENCHMARK_DOWNLOAD_DEPENDENCIES=ON
    # INSTALL_COMMAND ""
    # INSTALL_DIR ${CMAKE_SOURCE_DIR}/deps/libs
    )

#file(MAKE_DIRECTORY ${THIRD_PARTY_INCLUDE_DIR})  # Must exist.

add_library(libbenchmark STATIC IMPORTED GLOBAL)
set_property(TARGET libbenchmark PROPERTY IMPORTED_LOCATION ${THIRD_PARTY_LIBS_DIR}/libbenchmark.a)
set_property(TARGET libbenchmark PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${THIRD_PARTY_INCLUDE_DIR})

add_dependencies(libbenchmark googlebenchmark)