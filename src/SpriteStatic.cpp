#include "LeoEngine/SpriteStatic.hpp"
#include "LeoEngine/Graphics.hpp"
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Logger.hpp"

namespace LeoEngine
{

    SpriteStatic::SpriteStatic()
    {

    }

    SpriteStatic::SpriteStatic(std::string textureFilename)
        : _textureFilename(textureFilename)
    {
        
    }

    SpriteStatic::SpriteStatic(std::string textureFilename, TextureDrawData textureDrawData)
        : _textureFilename(textureFilename),
          _textureDrawData(textureDrawData)
    {

    }

    void SpriteStatic::draw()
    {
        if (_textureDrawData.destinationRectangle != nullptr && (_textureDrawData.destinationRectangle->width == 0 || _textureDrawData.destinationRectangle->height == 0))
        {
            Services::get().getLogger()->debug("SpriteStatic", "Size has not been set yet.");
            return;
        }

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
            _textureDrawData.destinationRectangle = std::make_shared<Rectangle<int>>(x, y, 0, 0);
            return;
        }

        _textureDrawData.destinationRectangle->x = x;
        _textureDrawData.destinationRectangle->y = y;
    }

    void SpriteStatic::setSize(int width, int height)
    {
        if (_textureDrawData.destinationRectangle == nullptr)
        {
            _textureDrawData.destinationRectangle = std::make_shared<Rectangle<int>>(0, 0, width, height);
            return;
        }

        _textureDrawData.destinationRectangle->width = width;
        _textureDrawData.destinationRectangle->height = height;
    }

    void SpriteStatic::setSourceRectangle(std::shared_ptr<Rectangle<int>> sourceRectangle)
    {
        _textureDrawData.sourceRectangle = sourceRectangle;
    }

    void SpriteStatic::setDestinationRectangle(std::shared_ptr<Rectangle<int>> destinationRectangle)
    {
        _textureDrawData.destinationRectangle = destinationRectangle;
    }

    void SpriteStatic::setAngle(double angle)
    {
        _textureDrawData.angle = angle;
    }

    void SpriteStatic::setCenter(std::shared_ptr<Pair<int, int>> center)
    {
        _textureDrawData.center = center;
    }

    void SpriteStatic::setFlip(FlipType flip)
    {
        _textureDrawData.flip = flip;
    }

    void SpriteStatic::setTextureFilename(std::string filename)
    {
        _textureFilename = filename;
    }

}
