#ifndef SPRITE_STATIC_HPP
#define SPRITE_STATIC_HPP

#include <string>
#include "LeoEngine/TextureDrawData.hpp"
#include "LeoEngine/Rectangle.hpp"
#include "LeoEngine/Pair.hpp"

namespace LeoEngine
{

    class SpriteStatic
    {
    public:
        SpriteStatic();
        SpriteStatic(std::string textureFilename);
        SpriteStatic(std::string textureFilename, TextureDrawData textureDrawData);

        void draw();

        const TextureDrawData *getDrawData() const;

        void setPosition(int x, int y);
        void setSize(int width, int height);

        void setSourceRectangle(std::shared_ptr<Rectangle> sourceRectangle);
        void setDestinationRectangle(std::shared_ptr<Rectangle> destinationRectangle);
        void setAngle(double angle);
        void setCenter(std::shared_ptr<Pair<int, int>> center);
        void setFlip(FlipType flip);

        void setTextureFilename(std::string filename);

    private:
        std::string _textureFilename;
        TextureDrawData _textureDrawData;
    };

}

#endif

