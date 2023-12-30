include(FetchContent)
FetchContent_Declare(
    asyncio
    URL https://codeload.github.com/ywy2090/asyncio/zip/8b9b47f117745e4aeafc0e070cc4dbadaf49700a
    URL_HASH MD5=1720a105b2dcd0c8ac33bc199f848034
    )

# CMake 3.14+
FetchContent_MakeAvailable(asyncio)