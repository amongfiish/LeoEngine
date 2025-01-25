#ifndef PAIR_HPP
#define PAIR_HPP

#if defined(__linux__) || defined(__APPLE__)
    #include <SDL2/SDL.h>
#elif defined(_WIN32)
    #include <SDL.h>
#endif

namespace LeoEngine
{

    template<class T0, class T1>
    class Pair
    {
    public:
        Pair() = default;

        Pair(T0 first, T1 second)
            : first(first),
            second(second)
        {
        }

        SDL_Point toSDLPoint() const
        {
            SDL_Point newPoint = { first, second };

            return newPoint;
        }

        T0 first;
        T1 second;
    };

}

#endif

