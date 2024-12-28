#include "LeoEngine/Sprite.hpp"
#include "LeoEngine/Graphics.hpp"
#include "LeoEngine/Services.hpp"

namespace LeoEngine
{

    Sprite::Sprite()
    {

    }

    Sprite::Sprite(string textureFilename)
        : _textureFilename(textureFilename)
    {
        
    }

    Sprite::Sprite(string textureFilename, TextureDrawData textureDrawData)
        : _textureFilename(textureFilename),
          _textureDrawData(textureDrawData)
    {

    }

    void Sprite::draw()
    {
        Services::get().getGraphics()->drawTexture(_textureFilename, _textureDrawData);
    }

    const TextureDrawData *Sprite::getDrawData() const
    {
        return &_textureDrawData;
    }

    void Sprite::setPosition(int x, int y)
    {
        if (_textureDrawData.destinationRectangle == nullptr)
        {
            _textureDrawData.destinationRectangle = make_shared<Rectangle>(x, y, 0, 0);
            return;
        }

        _textureDrawData.destinationRectangle->x = x;
        _textureDrawData.destinationRectangle->y = y;
    }

    void Sprite::setSize(int width, int height)
    {
        if (_textureDrawData.destinationRectangle == nullptr)
        {
            _textureDrawData.destinationRectangle = make_shared<Rectangle>(0, 0, width, height);
            return;
        }

        _textureDrawData.destinationRectangle->width = width;
        _textureDrawData.destinationRectangle->height = height;
    }

    void Sprite::setSourceRectangle(shared_ptr<Rectangle> sourceRectangle)
    {
        _textureDrawData.sourceRectangle = sourceRectangle;
    }

    void Sprite::setDestinationRectangle(shared_ptr<Rectangle> destinationRectangle)
    {
        _textureDrawData.destinationRectangle = destinationRectangle;
    }

    void Sprite::setAngle(double angle)
    {
        _textureDrawData.angle = angle;
    }

    void Sprite::setCenter(shared_ptr<Pair<int, int>> center)
    {
        _textureDrawData.center = center;
    }

    void Sprite::setFlip(FlipType flip)
    {
        _textureDrawData.flip = flip;
    }

    void Sprite::setTextureFilename(string filename)
    {
        _textureFilename = filename;
    }

}
