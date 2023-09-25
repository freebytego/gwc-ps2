#ifndef HELPER_H
#define HELPER_H

#include <tyra>
#include <sstream>
#include <string>

// #define RUNNING_FROM_DISC

class Helper
{

public:
    static std::string fromCwd(const std::string& path);

};


#endif // HELPER_H