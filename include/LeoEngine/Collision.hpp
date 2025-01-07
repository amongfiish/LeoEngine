#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "LeoEngine/Rectangle.hpp"
#include "LeoEngine/Circle.hpp"

namespace LeoEngine
{

    bool checkForOverlap(const Rectangle &r1, const Rectangle &r2);
    bool checkForOverlap(const Rectangle &r, const Circle &c);
    bool checkForOverlap(const Circle &c, const Rectangle &r);
    bool checkForOverlap(const Circle &c1, const Circle &c2);

}

#endif
