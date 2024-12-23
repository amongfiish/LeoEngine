#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#if defined(__linux__) || defined(__APPLE__)
    #include <SDL2/SDL.h>
#elif defined(_WIN32)
    #include <SDL.h>
#endif

#include <string>
using namespace std;

class Texture
{
public:
    Texture(string path);
    ~Texture();

    SDL_Texture *getSDLTextureObject();

private:
    SDL_Texture *_texture = nullptr;
};

#endif

