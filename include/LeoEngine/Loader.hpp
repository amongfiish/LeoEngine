#ifndef LOADER_HPP
#define LOADER_HPP

#include <SDL3/SDL.h>

#include <unordered_map>
#include <string>

#include "LeoEngine/File.hpp"

namespace LeoEngine
{

    template<class T>
    class Loader
    {
    public:
        Loader(std::string subdirectory)
        {
            const char PATH_SEPARATOR = File::getPathSeparator();
            const std::string APPLICATION_DATA_DIRECTORY = File::getApplicationDataDirectory();

            for (char& c : subdirectory) {
                if ((c == '\\' || c == '/') && c != PATH_SEPARATOR) {
                    c = PATH_SEPARATOR;
                }
            }

            _path = APPLICATION_DATA_DIRECTORY + subdirectory + PATH_SEPARATOR;
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

