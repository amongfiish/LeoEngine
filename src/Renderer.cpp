#include <stdexcept>
#include "Renderer.hpp"
using namespace std;

Renderer::Renderer(SDL_Window *window)
{
    SDL_Renderer *newRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (newRenderer == nullptr)
    {
        throw runtime_error("Renderer could not be created.");
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

void Renderer::setScalingFactor(float scalingX, float scalingY)
{
    SDL_RenderSetScale(_renderer, scalingX, scalingY);
}

void Renderer::setScalingFactor(const Pair<float, float>& scalingFactors)
{
    setScalingFactor(scalingFactors.first, scalingFactors.second);
}

void Renderer::setViewport(const Rectangle& viewport)
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
