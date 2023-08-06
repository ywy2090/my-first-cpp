
cmake_minimum_required(VERSION 3.1.0)

# message(STATUS "CMakeLists.txt for main")

# 通配符
# file(GLOB SRCS *.cpp) # 匹配当前目录下的.cpp文件
file(GLOB_RECURSE SRCS *.cpp) # 匹配当前目录所有子目录的.cpp文件

# 可执行程序
add_executable(${PROJECT_NAME} ${SRCS})

# 添加链接库
target_link_libraries(${PROJECT_NAME} PUBLIC ${MATH_TARGET})