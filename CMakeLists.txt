
# cmake版本号限制
cmake_minimum_required(VERSION 3.1.0)

# 将 C++ 标准设置为 C++ 20
set(CMAKE_CXX_STANDARD 20)  
# C++ 11 是强制要求，不会衰退至低版本
set(CMAKE_CXX_STANDARD_REQUIRED ON)  
# 禁止使用编译器特有扩展
set(CMAKE_CXX_EXTENSIONS OFF)  

# 设置工程名称
set(PROJECT_NAME my-first-cpp)

# 加载cmake模块
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# include GlobalSettings
include(GlobalSettings)

# 工程名
project(${PROJECT_NAME})

# 添加子目录
add_subdirectory(math)
add_subdirectory(main)

# ut
if(TESTS)
    add_subdirectory(test)
endif(TESTS)

# 基准测试
if(BENCH_MARK)
    add_subdirectory(benchmark)
endif(BENCH_MARK)