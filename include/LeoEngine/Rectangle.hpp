#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#if defined(__linux__) || defined(__APPLE__)
    #include <SDL2/SDL.h>
#elif defined (_WIN32)
    #include <SDL.h>
#endif

#include "LeoEngine/Pair.hpp"

namespace LeoEngine
{

    template<class T>
    class Rectangle
    {
    public:
        Rectangle()
            : Rectangle(0, 0, 0, 0)
        {

        }

        Rectangle(T x, T y, T width, T height)
            : x(x), y(y),
              width(width),
              height(height)
        {

        }

        Rectangle(Pair<T, T> position, Pair<T, T> dimensions)
            : x(position.first), y(position.second),
              width(dimensions.first), height(dimensions.second)
        {

        }

        SDL_Rect toSDLRect() const
        {
            SDL_Rect newRect = { static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height) };

            return newRect;
        }

        T getRight() const
        {
            return x + width;
        }

        T getBottom() const
        {
            return y + height;
        }

        T x;
        T y;
        T width;
        T height;
    };

}

#endif

