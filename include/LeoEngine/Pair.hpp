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

        LeoEngine::Pair<T0, T1> operator+(const Pair<T0, T1>& other) const
        {
            return LeoEngine::Pair<T0, T1>(first + other.first, second + other.second);
        }

        LeoEngine::Pair<T0, T1> operator-(const Pair<T0, T1>& other) const
        {
            return LeoEngine::Pair<T0, T1>(first - other.first, second - other.second);
        }

        LeoEngine::Pair<T0, T1> operator*(const Pair<T0, T1>& other) const
        {
            return LeoEngine::Pair<T0, T1>(first * other.first, second * other.second);
        }

        LeoEngine::Pair<T0, T1> operator/(const Pair<T0, T1>& other) const
        {
            return LeoEngine::Pair<T0, T1>(first / other.first, second / other.second);
        }

        LeoEngine::Pair<T0, T1> operator*(double multiple) const
        {
            return LeoEngine::Pair<T0, T1>(first * multiple, second * multiple);
        }

        template<class T2, class T3>
        operator LeoEngine::Pair<T2, T3>() const
        {
            return LeoEngine::Pair<T2, T3>(static_cast<T2>(first), static_cast<T3>(second));
        }

        T0 first;
        T1 second;
    };

}

#endif

