
# cmake版本号限制
cmake_minimum_required(VERSION 3.1.0)

# 设置工程名称
set(PROJECT_NAME my-first-cpp)

set(VERSION "1.0.0")
set(VERSION_SUFFIX "-beta")
# 工程名
project(${PROJECT_NAME} VERSION ${VERSION})

# Release Debug RelWithDebInfo MinSizeRel
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "RelWithDebInfo")
endif()


# 加载cmake模块
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
message(STATUS " CMAKE_MODULE_PATH => ${CMAKE_MODULE_PATH}")

# include GlobalSettings
include(GlobalSettings)
# include CompilerSettings
include(CompilerSettings)
# include BuildInfo
include(BuildInfo)
create_build_info()

# 添加include 目录
# include_directories(path/to/include/dir)
# link_directories(path/to/library/dir)
# target_name目标单独添加include目录
# target_include_directories(target_name PUBLIC path/to/include/dir)
# target_link_directories(target_name PUBLIC path/to/library/dir)

# 添加子模块
add_subdirectory(modules)
# 主函数
add_subdirectory(main)

# 基准测试
# if(BENCHMARKS)
#     add_subdirectory(benchmark)
# endif(BENCHMARKS)