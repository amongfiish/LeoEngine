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
            : sourceRectangle(nullptr),
            destinationRectangle(nullptr),
            angle(0),
            center(nullptr),
            flip(FlipType::NONE)
        {
        }

        TextureDrawData(std::shared_ptr<Rectangle<int>> srcRect, std::shared_ptr<Rectangle<int>> destRect, double angle, std::shared_ptr<Pair<int, int>> center, FlipType flip)
            : sourceRectangle(srcRect),
            destinationRectangle(destRect),
            angle(angle), center(center),
            flip(flip)
        {
        }

        std::shared_ptr<Rectangle<int>> sourceRectangle;
        std::shared_ptr<Rectangle<int>> destinationRectangle;
        double angle;
        std::shared_ptr<Pair<int, int>> center;
        FlipType flip;
    };

}

#endif

