# cmake version require
cmake_minimum_required(VERSION 3.14)

# project name
set(PROJECT_NAME my-first-cpp)

set(VERSION "1.0.0")
set(VERSION_SUFFIX "-beta")

# project name version
project(${PROJECT_NAME} VERSION ${VERSION} LANGUAGES C CXX)

# download deps url prefix, default download from github.com
if(NOT URL_PREFIX)
    set(URL_PREFIX "github.com")
endif(NOT URL_PREFIX)

# build type: Release Debug RelWithDebInfo MinSizeRel
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/ar)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Threads REQUIRED)

# add cmake module files
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

message(STATUS "PROJECT_BINARY_DIR => ${PROJECT_BINARY_DIR}")
message(STATUS "CMAKE_SOURCE_DIR => ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_BINARY_DIR => ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR => ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR => ${CMAKE_CURRENT_BINARY_DIR}")

# include GNUInstallDirs
include(GNUInstallDirs)

# include GlobalSettings
include(GlobalSettings)

# include CompilerSettings
include(CompilerSettings)

# include BuildInfoGenerator
include(BuildInfoGenerator)

# # ----------------- third party deps include begin ------------------------------

# nlohmann json
include(ProjectNlohmannJson)

# jsoncpp
include(ProjectJsonCpp)

# leveldb
include(ProjectLeveldb)

# spdlog
include(ProjectSpdLog)

# benchmark
if(BENCHMARKS)
    include(ProjectBenchmark)
    add_subdirectory(benchmarks)
endif(BENCHMARKS)

# # ----------------- third party deps include end ------------------------------

# # ----------------- third party deps find_pacakge begin ------------------------------

# readerwriterqueue
find_path(READERWRITERQUEUE_INCLUDE_DIRS "readerwriterqueue/atomicops.h")

# concurrentqueue
find_package(unofficial-concurrentqueue CONFIG REQUIRED)

# # ----------------- third party deps find_pacakge end ------------------------------

# TODO: target_xxx_xxx sample
# target_name add include directories for target
# target_include_directories(target_name PUBLIC path/to/include/dir)
# target_link_directories(target_name PUBLIC path/to/library/dir)

# sub modules
add_subdirectory(modules)

# main program
add_subdirectory(main)