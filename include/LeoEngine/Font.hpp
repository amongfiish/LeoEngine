#ifndef FONT_HPP
#define FONT_HPP

#if defined(__linux__) || defined(__APPLE__)
    #include <SDL_ttf.h>
#elif defined(_WIN32)
    #include <SDL_ttf.h>
#endif

#include <string>

namespace LeoEngine
{

    class Font
    {
    public:
        Font(std::string filepath);
        ~Font();

        TTF_Font *getSDLFontObject();

    private:
        TTF_Font *_font = nullptr;
    };

}

#endif

