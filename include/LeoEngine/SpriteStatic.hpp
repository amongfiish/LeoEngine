#ifndef SPRITE_STATIC_HPP
#define SPRITE_STATIC_HPP

#include <string>
#include "LeoEngine/TextureDrawData.hpp"
#include "LeoEngine/Rectangle.hpp"
#include "LeoEngine/Pair.hpp"
using namespace std;

namespace LeoEngine
{

    class SpriteStatic
    {
    public:
        SpriteStatic();
        SpriteStatic(string textureFilename);
        SpriteStatic(string textureFilename, TextureDrawData textureDrawData);

        void draw();

        const TextureDrawData *getDrawData() const;

        void setPosition(int x, int y);
        void setSize(int width, int height);

        void setSourceRectangle(shared_ptr<Rectangle> sourceRectangle);
        void setDestinationRectangle(shared_ptr<Rectangle> destinationRectangle);
        void setAngle(double angle);
        void setCenter(shared_ptr<Pair<int, int>> center);
        void setFlip(FlipType flip);

        void setTextureFilename(string filename);

    private:
        string _textureFilename;
        TextureDrawData _textureDrawData;
    };

}

#endif

