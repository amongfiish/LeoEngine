#ifndef PAIR_HPP
#define PAIR_HPP

#include <SDL3/SDL.h>

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

        Pair(const Pair<T0, T1>& other)
        {
            first = other.first;
            second = other.second;
        }

        SDL_Point toSDLPoint() const
        {
            SDL_Point newPoint = { first, second };

            return newPoint;
        }

        bool operator==(const Pair<T0, T1>& other) const
        {
            return (first == other.first && second == other.second);
        }

        T0 first;
        T1 second;
    };

}

#endif

