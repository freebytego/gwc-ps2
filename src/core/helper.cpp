#include "core/helper.hpp"

std::string Helper::fromCwd(const std::string& path)
{
    #ifndef RUNNING_FROM_DISC

    return Tyra::FileUtils::fromCwd(path);

    #else

    std::stringstream cdfsPath;
    cdfsPath << "cdfs:/" << path;
    return cdfsPath.str();

    #endif
}