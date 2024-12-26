#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <string>
#include "LeoEngine/TextureDrawData.hpp"
#include "LeoEngine/Rectangle.hpp"
#include "LeoEngine/Pair.hpp"
using namespace std;

namespace LeoEngine
{

    class Sprite
    {
    public:
        Sprite(string textureFilename);
        Sprite(string textureFilename, TextureDrawData textureDrawData);

        void draw();

        const TextureDrawData *getDrawData() const;

        void setPosition(int x, int y);

        void setSourceRectangle(shared_ptr<Rectangle> sourceRectangle);
        void setDestinationRectangle(shared_ptr<Rectangle> destinationRectangle);
        void setAngle(double angle);
        void setCenter(shared_ptr<Pair<int, int>> center);
        void setFlip(FlipType flip);

    private:
        string _textureFilename;
        TextureDrawData _textureDrawData;
    };

}

#endif

