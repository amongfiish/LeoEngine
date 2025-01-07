#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "LeoEngine/Pair.hpp"

namespace LeoEngine
{

    class Circle
    {
    public:
        Circle()
            : Circle(0, 0, 0)
        {
        
        }

        Circle(int x, int y, int radius)
            : x(x), y(y), radius(radius)
        {

        }

        ~Circle()
        {

        }

        const Pair<int, int> getCenter() const
        {
            return Pair<int, int>(x + radius, y + radius);
        }

        int x;
        int y;
        int radius;
    };

}

#endif
