#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL3/SDL.h>

#include "LeoEngine/Pair.hpp"
#include "LeoEngine/Rectangle.hpp"
#include "LeoEngine/Colour.hpp"

namespace LeoEngine
{

    class Renderer
    {
    public:
        Renderer(SDL_Window *window);
        ~Renderer();

        void setDrawColour(int r, int g, int b, int a);
        void setDrawColour(const Colour &colour);

        void setLogicalDimensions(int width, int height);
        void setLogicalDimensions(const Pair<int, int> &dimensions);

        Pair<int, int> getLogicalDimensions() const;
        Pair<int, int> getRenderDimensions() const;

        void setScalingFactor(float scalingX, float scalingY);
        void setScalingFactor(const Pair<float, float> &scalingFactors);

        void setViewport(const Rectangle<int> &viewport);

        void setVSync(bool useVSync);

        SDL_Renderer *getSDLRendererObject() const;

    private:
        SDL_Renderer *_renderer = nullptr;
    };

}

#endif

