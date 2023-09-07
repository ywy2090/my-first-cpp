# 设置全局使用的变量
set(MATH_TARGET "math")
set(LIB_LEVELDB_TARGET "libleveldb")
set(LIB_SPDLOG_TARGET "libspdlog")

message(STATUS "CMAKE_SOURCE_DIR => ${CMAKE_SOURCE_DIR}")
set(THIRD_PARTY_DIR ${CMAKE_SOURCE_DIR}/build/third_party/)
set(THIRD_PARTY_LIBS_DIR ${THIRD_PARTY_DIR}/lib/)
set(THIRD_PARTY_INCLUDE_DIR ${THIRD_PARTY_DIR}/include/)