#ifndef COLOUR_HPP
#define COLOUR_HPP

#include <SDL3/SDL.h>

namespace LeoEngine
{

    class Colour
    {
    public:
        Colour()
            : red(0x00),
              green(0x00),
              blue(0x00),
              alpha(0xFF)
        {}
        
        Colour(int red, int green, int blue, int alpha)
            : red(red),
              green(green),
              blue(blue),
              alpha(alpha)
        {}

        SDL_Color toSDLColor()
        {
            SDL_Color sdlColor = { static_cast<Uint8>(red), static_cast<Uint8>(green), static_cast<Uint8>(blue), static_cast<Uint8>(alpha) };
            return sdlColor;
        }

        bool operator!=(const Colour& other)
        {
            return (red != other.red) || (green != other.green) || (blue != other.blue) || (alpha != other.alpha);
        }

        Colour& operator=(const Colour& other)
        {
            red = other.red;
            green = other.green;
            blue = other.blue;
            alpha = other.alpha;

            return *this;
        }

        int red, green, blue, alpha;
    };

}

#endif

