# set(BENCHMARK_ENABLE_TESTING NO)
# include(FetchContent)
# FetchContent_Declare(
# googlebenchmark
# URL https://github.com/google/benchmark/archive/refs/tags/v1.8.3.zip
# )
# FetchContent_MakeAvailable(googlebenchmark)

include(ExternalProject)
ExternalProject_add(googlebenchmark
    PREFIX ${THIRD_PARTY_DIR}
    DOWNLOAD_NAME googlebenchmark-1.8.3.zip
    DOWNLOAD_NO_PROGRESS 1
    LOG_DOWNLOAD true
    LOG_BUILD true
    LOG_INSTALL true
    LOG_CONFIGURE true
    URL https://${URL_PREFIX}/google/benchmark/archive/refs/tags/v1.8.3.zip
    URL_HASH SHA256=abfc22e33e3594d0edf8eaddaf4d84a2ffc491ad74b6a7edc6e7a608f690e691
    CMAKE_ARGS -DBENCHMARK_ENABLE_TESTING=OFF
    -DCMAKE_INSTALL_PREFIX=${THIRD_PARTY_DIR}
    -DCMAKE_BUILD_TYPE=Release
    -DBENCHMARK_ENABLE_GTEST_TESTS=OFF
    -DBENCHMARK_DOWNLOAD_DEPENDENCIES=ON
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

    # INSTALL_COMMAND ""
    # INSTALL_DIR ${CMAKE_SOURCE_DIR}/deps/libs
)

file(MAKE_DIRECTORY ${THIRD_PARTY_INCLUDE_DIR}) # Must exist.
add_library(benchmark::benchmark STATIC IMPORTED GLOBAL)
set_property(TARGET benchmark::benchmark PROPERTY IMPORTED_LOCATION ${THIRD_PARTY_LIBS_DIR}/libbenchmark.a)
set_property(TARGET benchmark::benchmark PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${THIRD_PARTY_INCLUDE_DIR})

add_dependencies(benchmark::benchmark googlebenchmark)