#if defined(__linux__) || defined(__APPLE__)
    #include <SDL3/SDL.h>
    #define PATH_SEPARATOR '/'
#elif defined(_WIN32)
    #include <SDL.h>
    #define PATH_SEPARATOR '\\'
#endif

#include <stdexcept>

#include "LeoEngine/FontManager.hpp"
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Logger.hpp"

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
        if (filename.empty())
        {
            std::string errorMessage = "Empty filename provided to getFont.";
            Services::get().getLogger()->error("FontManager", errorMessage);
            Services::get().getLogger()->flush();
            throw std::runtime_error(errorMessage);
        }

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
            TTF_SetFontHinting(newFontSize, TTF_HINTING_NONE);
            if (newFontSize == nullptr)
            {
                std::string errorMessage = std::string("Failed to load font at path '" + fullPath + "'. SDL error text: '") + SDL_GetError() + "'.";
                Services::get().getLogger()->error("FontManager", errorMessage);
                Services::get().getLogger()->flush();
                throw std::runtime_error(errorMessage);
            }

            auto insertResult = foundFontName->second.insert(std::make_pair(pointSize, newFontSize));

            return insertResult.first->second;
        }

        auto insertResult0 = _fonts.insert(std::make_pair(filename, std::map<int, TTF_Font *>()));

        std::string fullPath = _path + filename;
        TTF_Font *newFontSize = TTF_OpenFont(fullPath.c_str(), pointSize);
        TTF_SetFontHinting(newFontSize, TTF_HINTING_NONE);
        if (newFontSize == nullptr)
        {
            std::string errorMessage = std::string("Failed to load font at path '" + fullPath + "'. SDL error text: '") + SDL_GetError() + "'.";
            Services::get().getLogger()->error("FontManager", errorMessage);
            Services::get().getLogger()->flush();
            throw std::runtime_error(errorMessage);
        }

        auto insertResult1 = insertResult0.first->second.insert(std::make_pair(pointSize, newFontSize));

        return insertResult1.first->second;
    }

}

