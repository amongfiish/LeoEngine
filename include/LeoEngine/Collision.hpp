#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "LeoEngine/Rectangle.hpp"
#include "LeoEngine/Circle.hpp"

namespace LeoEngine
{

    bool checkForOverlap(const Rectangle<int> &r1, const Rectangle<int> &r2);
    bool checkForOverlap(const Rectangle<int> &r, const Circle &c);
    bool checkForOverlap(const Circle &c, const Rectangle<int> &r);
    bool checkForOverlap(const Circle &c1, const Circle &c2);

}

#endif
