#ifndef FONT_MANAGER_HPP
#define FONT_MANAGER_HPP

#if defined(__linux__) || defined(__APPLE__)
    #include <SDL3_ttf/SDL_ttf.h>
#elif defined(_WIN32)
    #include <SDL_ttf.h>
#endif

#include <map>
#include <string>

namespace LeoEngine
{

    class FontManager
    {
    public:
        FontManager();
        ~FontManager();

        TTF_Font *getFont(std::string filename, int pointSize);

    private:
        std::string _path;

        std::map<std::string, std::map<int, TTF_Font *>> _fonts;
    };

}

#endif

