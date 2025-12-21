#if defined(__linux__) || defined(__APPLE__)
    #include <SDL3_image/SDL_image.h>
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
        : _texture(nullptr)
    {
        SDL_Surface *newTextureSurface = IMG_Load(path.c_str());
        if (newTextureSurface == nullptr)
        {
            std::string message = std::string("Failed to load surface from file with path '") + path + "'.";
            Services::get().getLogger()->error("Texture", message);
            Services::get().getLogger()->flush();
            throw std::runtime_error(message);
        }

        SDL_Texture *newTexture = SDL_CreateTextureFromSurface(Services::get().getGraphics()->getRenderer().getSDLRendererObject(), newTextureSurface);
        SDL_DestroySurface(newTextureSurface);
        if (newTexture == nullptr)
        {
            Services::get().getLogger()->error("Texture", "Couldn't create new texture from surface. From SDL: " + LeoEngine::Services::get().getLogger()->getSDLError());
            Services::get().getLogger()->flush();
            throw std::runtime_error("Couldn't create new texture from surface.");
        }

        // nearest scaling mode
        SDL_SetTextureScaleMode(newTexture, SDL_SCALEMODE_NEAREST);
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
            Services::get().getLogger()->error("Texture", "Failed to create texture from surface.");

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
        Pair<float, float> textureDimensions;
        if (_texture != nullptr)
        {
            SDL_GetTextureSize(_texture, &textureDimensions.first, &textureDimensions.second);
        }

        // SDL3 conversion artifact
        Pair<int, int> textureIntDimensions(textureDimensions.first, textureDimensions.second);

        return textureIntDimensions;
    }

    SDL_Texture *Texture::getSDLTextureObject()
    {
        return _texture;
    }

}

