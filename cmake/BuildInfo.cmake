function(create_build_info)
    # Set build platform; to be written to BuildInfo.h
    set(PROJECT_BUILD_OS "${CMAKE_SYSTEM_NAME}")

    if (CMAKE_COMPILER_IS_MINGW)
        set(PROJECT_BUILD_COMPILER "mingw")
    elseif (CMAKE_COMPILER_IS_MSYS)
        set(PROJECT_BUILD_COMPILER "msys")
    elseif (CMAKE_COMPILER_IS_GNUCXX)
        set(PROJECT_BUILD_COMPILER "g++")
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set(PROJECT_BUILD_COMPILER "clang")
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
        set(PROJECT_BUILD_COMPILER "appleclang")
    else ()
        set(PROJECT_BUILD_COMPILER "unknown")
    endif ()

    set(PROJECT_BUILD_PLATFORM "${PROJECT_BUILD_OS}/${PROJECT_BUILD_COMPILER}")

    if (CMAKE_BUILD_TYPE)
        set(_cmake_build_type ${CMAKE_BUILD_TYPE})
    else()
        set(_cmake_build_type "${CMAKE_CFG_INTDIR}")
    endif()
    # Generate header file containing useful build information
    add_custom_target(BuildInfo.h ALL
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} -DPROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}"
        -DPROJECT_BUILDINFO_IN="${CMAKE_SOURCE_DIR}/cmake/templates/BuildInfo.h.in"
        -DPROJECT_DST_DIR="${PROJECT_BINARY_DIR}/include"
        -DPROJECT_CMAKE_DIR="${CMAKE_SOURCE_DIR}/cmake"
        -DPROJECT_BUILD_TYPE="${_cmake_build_type}"
        -DPROJECT_BUILD_OS="${PROJECT_BUILD_OS}"
        -DPROJECT_BUILD_COMPILER="${PROJECT_BUILD_COMPILER}"
        -DPROJECT_BUILD_PLATFORM="${PROJECT_BUILD_PLATFORM}"
        -DPROJECT_VERSION_SUFFIX="${VERSION_SUFFIX}"
        -DPROJECT_VERSION="${PROJECT_VERSION}"
        -P "${CMAKE_SOURCE_DIR}/cmake/GenBuildInfo.cmake")
    include_directories(BEFORE "${PROJECT_BINARY_DIR}/include")
endfunction()
