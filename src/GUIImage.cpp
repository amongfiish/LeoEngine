#include "LeoEngine/GUIImage.hpp"
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Graphics.hpp"

namespace LeoEngine
{

    GUIImage::GUIImage(std::shared_ptr<Texture> texture)
        : _texture(texture)
    {
        Pair<int, int> textureDimensions = _texture->getDimensions();
        _objectDimensions.first = textureDimensions.first;
        _objectDimensions.second = textureDimensions.second;
    }

    GUIImage::~GUIImage()
    {

    }

    void GUIImage::update(Pair<int, int>& offset)
    {
        
    }

    void GUIImage::draw(Pair<int, int>& offset)
    {
        if (_texture == nullptr)
        {
            return;
        }

        TextureDrawData updatedDrawData(_textureDrawData);
        updatedDrawData.destinationRectangle->x += offset.first;
        updatedDrawData.destinationRectangle->y += offset.second;
        
        Services::get().getGraphics()->drawTextureCameraless(_texture, updatedDrawData);
    }

    void GUIImage::setSourceRectangle(std::shared_ptr<Rectangle<int>> sourceRectangle)
    {
        _textureDrawData.sourceRectangle = sourceRectangle;
    }

    void GUIImage::setDestinationRectangle(std::shared_ptr<Rectangle<int>> destinationRectangle)
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

