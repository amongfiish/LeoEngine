#ifndef RENDERER_HPP
#define RENDERER_HPP

#if defined(__linux__) || defined(__APPLE__)
    #include <SDL2/SDL.h>
#elif defined(_WIN32)
    #include <SDL.h>
#endif

#include "LeoEngine/Pair.hpp"
#include "LeoEngine/Rectangle.hpp"
#include "LeoEngine/Colour.hpp"
using namespace std;

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

        void setScalingFactor(float scalingX, float scalingY);
        void setScalingFactor(const Pair<float, float> &scalingFactors);

        void setViewport(const Rectangle &viewport);

        void setVSync(bool useVSync);

        SDL_Renderer *getSDLRendererObject() const;

    private:
        SDL_Renderer *_renderer = nullptr;
    };

}

#endif

