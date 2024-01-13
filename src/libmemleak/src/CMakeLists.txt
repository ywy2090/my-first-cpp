cmake_minimum_required(VERSION 3.14)

# wildcard
# file(GLOB SRCS *.cpp)
file(GLOB_RECURSE SRCS *.h *.cpp)

# set(MEM_LEAK_TARGET memleak)

add_library(${MEM_LEAK_TARGET} INTERFACE ${SRCS})
# target_include_directories(${MEM_LEAK_TARGET} PUBLIC .)
# target_link_libraries(${MEM_LEAK_TARGET} PUBLIC jsoncpp_static OpenSSL::SSL OpenSSL::Crypto)

# install library
# install(TARGETS ${MEM_LEAK_TARGET} EXPORT mathTargets ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}")
install(TARGETS ${MEM_LEAK_TARGET} ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}")
# install head files
install(DIRECTORY ${MEM_LEAK_TARGET} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/" FILES_MATCHING PATTERN "*.h")