#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#if defined(__linux__) || defined(__APPLE__)
    #include <SDL2/SDL.h>
#elif defined (_WIN32)
    #include <SDL.h>
#endif

namespace LeoEngine
{

    class Rectangle
    {
    public:
        Rectangle()
            : Rectangle(0, 0, 0, 0)
        {

        }

        Rectangle(int x, int y, int width, int height)
            : x(x), y(y),
            width(width),
            height(height)
        {

        }

        SDL_Rect toSDLRect() const
        {
            SDL_Rect newRect = { x, y, width, height };

            return newRect;
        }

        int x;
        int y;
        int width;
        int height;
    };

}

#endif

