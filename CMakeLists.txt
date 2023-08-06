
# cmake版本号限制
cmake_minimum_required(VERSION 3.1.0)

# 设置工程名称
set(PROJECT_NAME my-first-cpp)

set(VERSION "1.0.0")
set(VERSION_SUFFIX "-beta")
# 工程名
project(${PROJECT_NAME} VERSION ${VERSION})

# 将 C++ 标准设置为 C++ 20
set(CMAKE_CXX_STANDARD 20)  
# C++ 20 是强制要求，不会衰退至低版本
set(CMAKE_CXX_STANDARD_REQUIRED ON)  
# 禁止使用编译器特有扩展
set(CMAKE_CXX_EXTENSIONS OFF)  


# Release Debug RelWithDebInfo MinSizeRel
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "RelWithDebInfo")
endif()


# 加载cmake模块
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# include GlobalSettings
include(GlobalSettings)
# include BuildInfo
include(BuildInfo)
create_build_info()


# 添加include 目录
# include_directories(path/to/include/dir)
# link_directories(path/to/library/dir)
# target_name目标单独添加include目录
# target_include_directories(target_name PUBLIC path/to/include/dir)
# target_link_directories(target_name PUBLIC path/to/library/dir)

# 添加子目录
add_subdirectory(math)
add_subdirectory(main)

# 基准测试
if(BENCH_MARK)
    add_subdirectory(benchmark)
endif(BENCH_MARK)