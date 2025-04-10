#include "LeoEngine/GUIImage.hpp"
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Graphics.hpp"

namespace LeoEngine
{

    GUIImage::GUIImage(Texture *texture)
        : _texture(texture)
    {
        Pair<int, int> textureDimensions = _texture->getDimensions();
        _objectDimensions.first = textureDimensions.first;
        _objectDimensions.second = textureDimensions.second;
    }

    GUIImage::~GUIImage()
    {

    }

    void GUIImage::update()
    {

    }

    void GUIImage::draw()
    {
        if (_texture == nullptr)
        {
            return;
        }
        
        Services::get().getGraphics()->drawTextureCameraless(_texture, _textureDrawData);
    }

    void GUIImage::setSourceRectangle(std::shared_ptr<Rectangle> sourceRectangle)
    {
        _textureDrawData.sourceRectangle = sourceRectangle;
    }

    void GUIImage::setDestinationRectangle(std::shared_ptr<Rectangle> destinationRectangle)
    {
        _textureDrawData.destinationRectangle = destinationRectangle;
        
        _objectDimensions.first = destinationRectangle->width;
        _objectDimensions.second = destinationRectangle->height;
    }

    void GUIImage::setAngle(double angle)
    {
        _textureDrawData.angle = angle;
    }

    void GUIImage::setCenter(std::shared_ptr<Pair<int, int>> center)
    {
        _textureDrawData.center = center;
    }

    void GUIImage::setFlip(FlipType flip)
    {
        _textureDrawData.flip = flip;
    }

}

