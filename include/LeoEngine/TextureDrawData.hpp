#ifndef TEXTURE_DRAW_DATA
#define TEXTURE_DRAW_DATA

#include <memory>
#include "LeoEngine/Rectangle.hpp"
#include "LeoEngine/Pair.hpp"
using namespace std;

namespace LeoEngine
{

    enum class FlipType
    {
        NONE,
        HORIZONTAL,
        VERTICAL
    };

    class TextureDrawData
    {
    public:
        TextureDrawData()
            : sourceRectangle(NULL),
            destinationRectangle(NULL),
            angle(0),
            center(NULL),
            flip(FlipType::NONE)
        {
        }

        TextureDrawData(shared_ptr<Rectangle> srcRect, shared_ptr<Rectangle> destRect, double angle, shared_ptr<Pair<int, int>> center, FlipType flip)
            : sourceRectangle(srcRect),
            destinationRectangle(destRect),
            angle(angle), center(center),
            flip(flip)
        {
        }

        shared_ptr<Rectangle> sourceRectangle;
        shared_ptr<Rectangle> destinationRectangle;
        double angle;
        shared_ptr<Pair<int, int>> center;
        FlipType flip;
    };

}

#endif

