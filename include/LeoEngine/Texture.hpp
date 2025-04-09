#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#if defined(__linux__) || defined(__APPLE__)
    #include <SDL2/SDL.h>
#elif defined(_WIN32)
    #include <SDL.h>
#endif

#include <string>
#include "LeoEngine/Pair.hpp"
using namespace std;

namespace LeoEngine
{

    class Texture
    {
    public:
        Texture(std::string path);
        ~Texture();

        Pair<int, int> getDimensions() const;

        SDL_Texture *getSDLTextureObject();

    private:
        SDL_Texture *_texture = nullptr;
    };

}

#endif

