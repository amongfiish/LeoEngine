#include "LeoEngine/SpriteStatic.hpp"
#include "LeoEngine/Graphics.hpp"
#include "LeoEngine/Services.hpp"

namespace LeoEngine
{

    SpriteStatic::SpriteStatic()
    {

    }

    SpriteStatic::SpriteStatic(string textureFilename)
        : _textureFilename(textureFilename)
    {
        
    }

    SpriteStatic::SpriteStatic(string textureFilename, TextureDrawData textureDrawData)
        : _textureFilename(textureFilename),
          _textureDrawData(textureDrawData)
    {

    }

    void SpriteStatic::draw()
    {
        Services::get().getGraphics()->drawTexture(_textureFilename, _textureDrawData);
    }

    const TextureDrawData *SpriteStatic::getDrawData() const
    {
        return &_textureDrawData;
    }

    void SpriteStatic::setPosition(int x, int y)
    {
        if (_textureDrawData.destinationRectangle == nullptr)
        {
            _textureDrawData.destinationRectangle = make_shared<Rectangle>(x, y, 0, 0);
            return;
        }

        _textureDrawData.destinationRectangle->x = x;
        _textureDrawData.destinationRectangle->y = y;
    }

    void SpriteStatic::setSize(int width, int height)
    {
        if (_textureDrawData.destinationRectangle == nullptr)
        {
            _textureDrawData.destinationRectangle = make_shared<Rectangle>(0, 0, width, height);
            return;
        }

        _textureDrawData.destinationRectangle->width = width;
        _textureDrawData.destinationRectangle->height = height;
    }

    void SpriteStatic::setSourceRectangle(shared_ptr<Rectangle> sourceRectangle)
    {
        _textureDrawData.sourceRectangle = sourceRectangle;
    }

    void SpriteStatic::setDestinationRectangle(shared_ptr<Rectangle> destinationRectangle)
    {
        _textureDrawData.destinationRectangle = destinationRectangle;
    }

    void SpriteStatic::setAngle(double angle)
    {
        _textureDrawData.angle = angle;
    }

    void SpriteStatic::setCenter(shared_ptr<Pair<int, int>> center)
    {
        _textureDrawData.center = center;
    }

    void SpriteStatic::setFlip(FlipType flip)
    {
        _textureDrawData.flip = flip;
    }

    void SpriteStatic::setTextureFilename(string filename)
    {
        _textureFilename = filename;
    }

}
