#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#if defined(__linux__) || defined(__APPLE__)
    #include <SDL3/SDL.h>
#elif defined(_WIN32)
    #include <SDL.h>
#endif

#include <string>
#include "LeoEngine/Pair.hpp"

namespace LeoEngine
{

    class Texture
    {
    public:
        // fancy, standard constructor
        Texture(std::string path);
        // raw (?) constructors
        Texture(SDL_Texture *sdlTexture);
        // DOES NOT FREE THE SURFACE!!!! BE CAREFUL!!!!
        Texture(SDL_Surface *sdlTexture);
        ~Texture();

        Pair<int, int> getDimensions() const;

        SDL_Texture *getSDLTextureObject();

    private:
        SDL_Texture *_texture = nullptr;
    };

}

#endif

