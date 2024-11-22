#ifndef FONT_HPP
#define FONT_HPP

#if defined(__linux__) || defined(__APPLE__)
    #include <SDL2/SDL_ttf.h>
#elif defined(_WIN32)
    #include <SDL_ttf.h>
#endif

#include <string>
using namespace std;

class Font
{
public:
    Font(string filepath);
    ~Font();

    TTF_Font *getSDLFontObject();

private:
    TTF_Font *_font = nullptr;
};

#endif

