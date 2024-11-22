#if defined(__linux__) || defined(__APPLE__)
    #include <SDL2/SDL_image.h>
#elif defined(_WIN32)
    #include <SDL_image.h>
#endif

#include <stdexcept>
#include "Texture.hpp"
#include "Graphics.hpp"
#include "Services.hpp"
using namespace std;

Texture::Texture(string path)
{
    SDL_Surface *newTextureSurface = IMG_Load(path.c_str());
    if (newTextureSurface == nullptr)
    {
        throw runtime_error("Couldn't load new texture from file.");
    }

    SDL_Texture *newTexture = SDL_CreateTextureFromSurface(Services::get().getGraphics()->getRenderer().getSDLRendererObject(), newTextureSurface);
    SDL_FreeSurface(newTextureSurface);
    if (newTexture == nullptr)
    {
        throw runtime_error("Couldn't create new texture from surface.");
    }

    _texture = newTexture;
}

Texture::~Texture()
{
    SDL_DestroyTexture(_texture);
}

SDL_Texture *Texture::getSDLTextureObject()
{
    return _texture;
}

