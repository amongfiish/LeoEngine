#ifndef CIRCLE_HPP
#define CIRCLE_HPP

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

        int x;
        int y;
        int radius;
    };

}

#endif
