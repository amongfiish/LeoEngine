#ifndef PAIR_HPP
#define PAIR_HPP

#include <SDL3/SDL.h>
#include <string>

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

        Pair<T0, T1> operator*(const Pair<T0, T1>& other) const
        {
            return Pair<T0, T1>(first * other.first, second * other.second);
        }

        Pair<T0, T1> operator*(const T0& multiplier) const
        {
            return Pair<T0, T1>(first * multiplier, second * multiplier);
        }

        void operator*=(const Pair<T0, T1>& other)
        {
            first *= other.first;
            second *= other.second;
        }

        void operator*=(const T0& multiplier)
        {
            first *= multiplier;
            second *= multiplier;
        }

        Pair<T0, T1> operator/(const Pair<T0, T1>& other) const
        {
            return Pair<T0, T1>(first / other.first, second / other.second);
        }

        Pair<T0, T1> operator/(const T0& divisor) const
        {
            return Pair<T0, T1>(first / divisor, second / divisor);
        }

        void operator/=(const Pair<T0, T1>& other)
        {
            first /= other.first;
            second /= other.second;
        }

        void operator/=(const T0 divisor)
        {
            first /= divisor;
            second /= divisor;
        }

        Pair<T0, T1> operator+(const Pair<T0, T1>& other) const
        {
            return Pair<T0, T1>(first + other.first, second + other.second);
        }

        void operator+=(const Pair<T0, T1>& other)
        {
            first += other.first;
            second += other.second;
        }

        Pair<T0, T1> operator-(const Pair<T0, T1>& other) const
        {
            return Pair<T0, T1>(first - other.first, second - other.second);
        }

        void operator-=(const Pair<T0, T1>& other)
        {
            first -= other.first;
            second -= other.second;
        }

        Pair<T0, T1> operator-() const
        {
            return Pair<T0, T1>(-first, -second);
        }

        std::string toString() const
        {
            std::string s = "Pair(" + std::to_string(first) + "," + std::to_string(second) + ")";
            return s;
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

