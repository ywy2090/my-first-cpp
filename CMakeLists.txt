# cmake version require
cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME my-first-cpp)

set(VERSION "1.0.0")
set(VERSION_SUFFIX "-beta")

# project name version
project(${PROJECT_NAME} VERSION ${VERSION} LANGUAGES C CXX)

# Release Debug RelWithDebInfo MinSizeRel
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "RelWithDebInfo")
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# add cmake module files
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
message(STATUS "CMAKE_MODULE_PATH => ${CMAKE_MODULE_PATH}")
message(STATUS "PROJECT_BINARY_DIR => ${PROJECT_BINARY_DIR}")
# message(STATUS "CMAKE_SOURCE_DIR => ${CMAKE_SOURCE_DIR}")
# message(STATUS "CMAKE_BINARY_DIR => ${CMAKE_BINARY_DIR}")
# message(STATUS "CMAKE_LIB_DIR => ${CMAKE_LIB_DIR}")
# message(STATUS "CMAKE_INCLUDE_DIR => ${CMAKE_INCLUDE_DIR}")
# message(STATUS "CMAKE_INSTALL_LIBDIR => ${CMAKE_INSTALL_LIBDIR}")
# message(STATUS "CMAKE_INSTALL_INCLUDEDIR => ${CMAKE_INSTALL_INCLUDEDIR}")
# message(STATUS "CMAKE_CURRENT_LIST_DIR => ${CMAKE_CURRENT_LIST_DIR}")
# message(STATUS "CMAKE_CURRENT_SOURCE_DIR => ${CMAKE_CURRENT_SOURCE_DIR}")
# message(STATUS "CMAKE_CURRENT_BINARY_DIR => ${CMAKE_CURRENT_BINARY_DIR}")

# include GlobalSettings
include(GlobalSettings)

# include CompilerSettings
include(CompilerSettings)

# include BuildInfoGenerator
include(BuildInfoGenerator)

# include BuildInfoGenerator
include(ProjectSpdLog)

# benchmark
if(BENCHMARKS)
    include(ProjectBenchmark)
endif(BENCHMARKS)

include(ProjectLeveldb)

# add include directories
# include_directories(path/to/include/dir)
# link_directories(path/to/library/dir)
# target_name add include directories for target
# target_include_directories(target_name PUBLIC path/to/include/dir)
# target_link_directories(target_name PUBLIC path/to/library/dir)

# sub modules
add_subdirectory(modules)

# main program
add_subdirectory(main)