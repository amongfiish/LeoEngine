#ifndef FILE_UTILITY_HPP
#define FILE_UTILITY_HPP

#include <string>

namespace LeoEngine
{

    struct FileUtility
    {
        static std::string getBasePath();
        static const char PATH_SEPARATOR;
    };

}

#endif

