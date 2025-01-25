#ifndef TEXTURE_DRAW_DATA
#define TEXTURE_DRAW_DATA

#include <memory>
#include "LeoEngine/Rectangle.hpp"
#include "LeoEngine/Pair.hpp"

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

        TextureDrawData(std::shared_ptr<Rectangle> srcRect, std::shared_ptr<Rectangle> destRect, double angle, std::shared_ptr<Pair<int, int>> center, FlipType flip)
            : sourceRectangle(srcRect),
            destinationRectangle(destRect),
            angle(angle), center(center),
            flip(flip)
        {
        }

        std::shared_ptr<Rectangle> sourceRectangle;
        std::shared_ptr<Rectangle> destinationRectangle;
        double angle;
        std::shared_ptr<Pair<int, int>> center;
        FlipType flip;
    };

}

#endif

