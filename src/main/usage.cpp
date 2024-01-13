
#include "usage.h"
#include "BuildInfo.h"
#include <fmt/format.h>

// using namespace initializer;

void initializer::printVersion()
{
    // fmt::print("fmt::fmt main");
    fmt::print("Project Version    : {}\n", PROJECT_PROJECT_VERSION);
    fmt::print("Build Time         : {}\n", PROJECT_BUILD_TIME);
    fmt::print("Build Type         : {}/{}\n", PROJECT_BUILD_PLATFORM, PROJECT_BUILD_TYPE);
    fmt::print("Git Branch         : {}\n", PROJECT_BUILD_BRANCH);
    fmt::print("Git Commit         : {}\n", PROJECT_COMMIT_HASH);
}