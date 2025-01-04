#ifndef RENDER_TARGET_HPP
#define RENDER_TARGET_HPP

#if defined(_WIN32)
    #include <SDL.h>
#elif defined(__linux__) || defined(__APPLE__)
    #include <SDL2/SDL.h>
#endif

#include <stdexcept>
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Graphics.hpp"
#include "LeoEngine/Logger.hpp"
using namespace std;

namespace LeoEngine
{

    class RenderTarget
    {
    public:
        RenderTarget(int width, int height)
        {
            _texture = SDL_CreateTexture(Services::get().getGraphics()->getRenderer().getSDLRendererObject(), SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, width, height);
            if (_texture == nullptr)
            {
                Services::get().getLogger()->critical("RenderTarget", "Failed to create new RenderTarget texture.");
                throw runtime_error("Failed to create render target.");
            }

            SDL_SetTextureBlendMode(_texture, SDL_BLENDMODE_BLEND);
        }

        ~RenderTarget()
        {
            if (_texture != nullptr)
            {
                SDL_DestroyTexture(_texture);
                _texture = nullptr;
            }
        }

        SDL_Texture *getSDLTextureObject()
        {
            return _texture;
        }

    private:
        SDL_Texture *_texture;
    };

}

#endif
