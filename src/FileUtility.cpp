#if defined(__linux__) || defined(__APPLE__)
    #include <SDL3/SDL.h>
#elif defined(_WIN32)
    #include <SDL.h>
#endif

#include "LeoEngine/FileUtility.hpp"

namespace LeoEngine
{

#ifdef _WIN32
    const char FileUtility::PATH_SEPARATOR = '\\';
#else
    const char FileUtility::PATH_SEPARATOR = '/';
#endif

    std::string FileUtility::getBasePath()
    {
        return SDL_GetBasePath();
    }

}

