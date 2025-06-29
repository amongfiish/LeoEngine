#include <stdexcept>
#include "LeoEngine/Renderer.hpp"

namespace LeoEngine
{

    Renderer::Renderer(SDL_Window *window)
    {
        SDL_Renderer *newRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (newRenderer == nullptr)
        {
            throw std::runtime_error("Renderer could not be created.");
        }

        SDL_SetRenderDrawBlendMode(newRenderer, SDL_BLENDMODE_BLEND);

        _renderer = newRenderer;
    }

    Renderer::~Renderer()
    {
        if (_renderer != nullptr)
        {
            SDL_DestroyRenderer(_renderer);
        }
    }

    void Renderer::setDrawColour(int r, int g, int b, int a)
    {
        SDL_SetRenderDrawColor(_renderer, r, g, b, a);
    }

    void Renderer::setDrawColour(const Colour& colour)
    {
        setDrawColour(colour.red, colour.green, colour.blue, colour.alpha);
    }

    void Renderer::setLogicalDimensions(int width, int height)
    {
        SDL_RenderSetLogicalSize(_renderer, width, height);
    }

    void Renderer::setLogicalDimensions(const Pair<int, int>& dimensions)
    {
        setLogicalDimensions(dimensions.first, dimensions.second);
    }

    Pair<int, int> Renderer::getLogicalDimensions() const
    {
        Pair<int, int> dimensions;
        SDL_RenderGetLogicalSize(_renderer, &dimensions.first, &dimensions.second);

        return dimensions;
    }

    void Renderer::setScalingFactor(float scalingX, float scalingY)
    {
        SDL_RenderSetScale(_renderer, scalingX, scalingY);
    }

    void Renderer::setScalingFactor(const Pair<float, float>& scalingFactors)
    {
        setScalingFactor(scalingFactors.first, scalingFactors.second);
    }

    void Renderer::setViewport(const Rectangle<int>& viewport)
    {
        SDL_Rect newRect = viewport.toSDLRect();
        SDL_RenderSetViewport(_renderer, &newRect);
    }

    void Renderer::setVSync(bool useVSync)
    {
        SDL_RenderSetVSync(_renderer, static_cast<int>(useVSync));
    }

    SDL_Renderer *Renderer::getSDLRendererObject() const
    {
        return _renderer;
    }

}
