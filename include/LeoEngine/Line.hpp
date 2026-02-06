#ifndef LINE_HPP
#define LINE_HPP

#include "LeoEngine/Pair.hpp"

namespace LeoEngine
{

    class Line
    {
    public:
        Line()
            : Line(0, 0, 0, 0)
        {

        }

        Line(int x1, int y1, int x2, int y2)
            : start(x1, y1), end(x2, y2)
        {

        }

        Line(Pair<int, int> &start, Pair<int, int> &end)
            : start(start), end(end)
        {

        }

        Pair<int, int> start;
        Pair<int, int> end;
    };

}

#endif

