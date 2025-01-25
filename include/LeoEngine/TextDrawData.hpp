#ifndef TEXT_DRAW_DATA_HPP
#define TEXT_DRAW_DATA_HPP

#include <string>
#include "LeoEngine/Colour.hpp"

namespace LeoEngine
{

    class TextDrawData
    {
    public:
        TextDrawData(string fontFilename, int pointSize, Colour &colour)
            : fontFilename(fontFilename),
            pointSize(pointSize),
            colour(colour)
        {
        }

        string fontFilename;
        int pointSize;
        Colour &colour;
    };

}

#endif

