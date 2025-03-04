#include "LeoEngine/Collision.hpp"
#include <cmath>

namespace LeoEngine
{
    bool checkForOverlap(const Rectangle &r1, const Rectangle &r2)
    {
        if (r1.getRight() > r2.x && r1.x < r2.getRight() && r1.getBottom() > r2.y && r1.y < r2.getBottom())
        {
            return true;
        }

        return false;
    }

    bool checkForOverlap(const Rectangle &r, const Circle &c)
    {
        const Pair<int, int> cCenter = c.getCenter();
        
        int testX = cCenter.first;
        int testY = cCenter.second;

        if (cCenter.first < r.x)
        {
            testX = r.x;
        }
        else if (cCenter.first > r.getRight())
        {
            testX = r.getRight();
        }

        if (cCenter.second < r.y)
        {
            testY = r.y;
        }
        else if (cCenter.second > r.getBottom())
        {
            testY = r.getBottom();
        }

        double distanceX = testX - cCenter.first;
        double distanceY = testY - cCenter.second;

        double distance = sqrt((distanceX * distanceX) + (distanceY * distanceY));

        if (distance <= c.radius)
        {
            return true;
        }

        return false;
    }

    bool checkForOverlap(const Circle &c, const Rectangle &r)
    {
        return checkForOverlap(r, c);
    }

    bool checkForOverlap(const Circle &c1, const Circle &c2)
    {
        double distanceX = c2.x - c1.x;
        double distanceY = c2.y - c1.y;

        double distance = sqrt((distanceX * distanceX) + (distanceY * distanceY));

        if (distance < (c1.radius + c2.radius))
        {
            return true;
        }

        return false;
    }

}
