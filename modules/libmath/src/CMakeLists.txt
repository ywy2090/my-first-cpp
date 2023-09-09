cmake_minimum_required(VERSION 3.10.0)

# wildcard
# file(GLOB SRCS *.cpp)
file(GLOB_RECURSE SRCS *.cpp)

add_library(${MATH_TARGET} ${SRCS})

# add include directory
target_include_directories(${MATH_TARGET} PUBLIC .)
# add link libraries
# target_link_libraries(${MATH_TARGET} PUBLIC jsoncpp_static OpenSSL::SSL OpenSSL::Crypto)

# install library
# install(TARGETS ${MATH_TARGET} EXPORT mathTargets ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}")
install(TARGETS ${MATH_TARGET} ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}")
# install head files
install(DIRECTORY ${MATH_TARGET} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/" FILES_MATCHING PATTERN "*.h")