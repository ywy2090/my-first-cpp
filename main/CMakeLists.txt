cmake_minimum_required(VERSION 3.1.0)

# 通配符
# file(GLOB SRCS *.cpp) # 匹配当前目录下的.cpp文件
file(GLOB_RECURSE SRCS *.cpp) # 匹配当前目录所有子目录的.cpp文件

# 添加vcpkg依赖
# find_package(fmt REQUIRED)
# find_package(range-v3 REQUIRED)
# find_package(cxxopts REQUIRED)

# 可执行程序
add_executable(${PROJECT_NAME} ${SRCS})

# link libraris for main excutable
target_link_libraries(${PROJECT_NAME} PRIVATE ${MATH_TARGET} ${LIB_SPDLOG_TARGET})