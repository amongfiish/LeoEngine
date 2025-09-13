#ifndef LOADER_HPP
#define LOADER_HPP

#if defined(__linux__) || defined(__APPLE__)
    #include <SDL2/SDL.h>
#elif defined(_WIN32)
    #include <SDL.h>
#endif

#include <unordered_map>
#include <string>

namespace LeoEngine
{

#ifdef _WIN32
#define PATH_SEPARATOR '\\'
#else
#define PATH_SEPARATOR '/'
#endif

    template<class T>
    class Loader
    {
    public:
        Loader(std::string subdirectory)
        {
            std::string basePath = SDL_GetBasePath();

            for (char& c : subdirectory) {
                if ((c == '\\' || c == '/') && c != PATH_SEPARATOR) {
                    c = PATH_SEPARATOR;
                }
            }

            _path = basePath + subdirectory + PATH_SEPARATOR;
        }

        ~Loader()
        {

        }

        T &get(std::string filename)
        {
            std::string pathToFile = _path + filename;

            auto foundResource = _resources.find(filename);
            if (foundResource == _resources.end()) {
                return (*(_resources.emplace(filename, pathToFile).first)).second;
            }

            return (*foundResource).second;
        }

    private:
        std::string _path;

        std::unordered_map<std::string, T> _resources;
    };

}

#endif

