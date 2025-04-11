#include "LeoEngine/FontManager.hpp"

#if defined(__linux__) || defined(__APPLE__)
    #include <SDL2/SDL.h>
    #define PATH_SEPARATOR '/'
#elif defined(_WIN32)
    #include <SDL.h>
    #define PATH_SEPARATOR '\\'
#endif

namespace LeoEngine
{

    FontManager::FontManager()
    {
        std::string basePath = SDL_GetBasePath();
        _path = basePath + "fonts" + PATH_SEPARATOR;
    }

    FontManager::~FontManager()
    {
        for (auto it0 = _fonts.begin(); it0 != _fonts.end(); it0++)
        {
            for (auto it1 = it0->second.begin(); it1 != it0->second.end(); it1++)
            {
                TTF_CloseFont(it1->second);
            }
        }
    }

    TTF_Font *FontManager::getFont(std::string filename, int pointSize)
    {
        auto foundFontName = _fonts.find(filename);
        if (foundFontName != _fonts.end())
        {
            auto foundFont = foundFontName->second.find(pointSize);
            if (foundFont != foundFontName->second.end())
            {
                return foundFont->second;
            }

            std::string fullPath = _path + filename;
            TTF_Font *newFontSize = TTF_OpenFont(fullPath.c_str(), pointSize);
            auto insertResult = foundFontName->second.insert(std::make_pair(pointSize, newFontSize));

            return insertResult.first->second;
        }

        auto insertResult0 = _fonts.insert(std::make_pair(filename, std::map<int, TTF_Font *>()));
        std::string fullPath = _path + filename;
        TTF_Font *newFontSize = TTF_OpenFont(fullPath.c_str(), pointSize);

        auto insertResult1 = insertResult0.first->second.insert(std::make_pair(pointSize, newFontSize));
        return insertResult1.first->second;
    }

}

