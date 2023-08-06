#include "BuildInfo.h"
#include "MyMath.h"
#include <cstring>
#include <iostream>

void printVersion()
{
    std::cout << "Project Version    : " << PROJECT_PROJECT_VERSION << std::endl;
    std::cout << "Build Time         : " << PROJECT_BUILD_TIME << std::endl;
    std::cout << "Build Type         : " << PROJECT_BUILD_PLATFORM << "/" << PROJECT_BUILD_TYPE
              << std::endl;
    std::cout << "Git Branch         : " << PROJECT_BUILD_BRANCH << std::endl;
    std::cout << "Git Commit         : " << PROJECT_COMMIT_HASH << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc >= 1 && ((0 == strncmp(argv[1], "-v", 2) || 0 == strncmp(argv[1], "--version", 8))))
    {
        printVersion();
        return 0;
    }

    {
        math::Math math;
        std::cout << "1 + 2 = " << math.add(1, 2) << std::endl;
    }

    return 0;
}