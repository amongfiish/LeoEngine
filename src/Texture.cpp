#if defined(__linux__) || defined(__APPLE__)
    #include <SDL_image.h>
#elif defined(_WIN32)
    #include <SDL_image.h>
#endif

#include <stdexcept>
#include "LeoEngine/Texture.hpp"
#include "LeoEngine/Graphics.hpp"
#include "LeoEngine/Logger.hpp"
#include "LeoEngine/Services.hpp"

namespace LeoEngine
{

    Texture::Texture(std::string path)
    {
        SDL_Surface *newTextureSurface = IMG_Load(path.c_str());
        if (newTextureSurface == nullptr)
        {
            std::string message = "File '";
            message = message + path + "' not found";
            Services::get().getLogger()->critical("Texture", message);
            Services::get().getLogger()->flush();
            throw std::runtime_error("Couldn't load new texture from file.");
        }

        SDL_Texture *newTexture = SDL_CreateTextureFromSurface(Services::get().getGraphics()->getRenderer().getSDLRendererObject(), newTextureSurface);
        SDL_FreeSurface(newTextureSurface);
        if (newTexture == nullptr)
        {
            Services::get().getLogger()->critical("Texture", "Couldn't create new texture from surface. From SDL: " + LeoEngine::Services::get().getLogger()->getSDLError());
            Services::get().getLogger()->flush();
            throw std::runtime_error("Couldn't create new texture from surface.");
        }

        _texture = newTexture;
    }

    Texture::Texture(SDL_Texture *texture)
    {
        _texture = texture;
    }

    Texture::Texture(SDL_Surface *surface)
    {
        SDL_Texture *newTexture = SDL_CreateTextureFromSurface(Services::get().getGraphics()->getRenderer().getSDLRendererObject(), surface);
        if (newTexture == nullptr)
        {
            Services::get().getLogger()->critical("Texture", "Failed to create texture from surface.");

            Services::get().getLogger()->flush();
            throw std::runtime_error("Failed to create texture from surface.");
        }

        _texture = newTexture;
    }

    Texture::~Texture()
    {
        SDL_DestroyTexture(_texture);
    }

    Pair<int, int> Texture::getDimensions() const
    {
        Pair<int, int> textureDimensions;

        if (_texture != nullptr)
        {
            SDL_QueryTexture(_texture, nullptr, nullptr, &textureDimensions.first, &textureDimensions.second);
        }

        return textureDimensions;
    }

    SDL_Texture *Texture::getSDLTextureObject()
    {
        return _texture;
    }

}
