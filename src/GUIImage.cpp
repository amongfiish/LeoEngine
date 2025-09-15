#include "LeoEngine/GUIImage.hpp"
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Graphics.hpp"

namespace LeoEngine
{

    GUIImage::GUIImage(std::string textureFilename)
        : _texture(LeoEngine::Services::get().getGraphics()->getTexture(textureFilename))
    {
        Pair<int, int> textureDimensions = _texture.getDimensions();
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
        TextureDrawData updatedDrawData(_textureDrawData);

        std::shared_ptr<LeoEngine::Rectangle<int>> destRect = std::make_shared<LeoEngine::Rectangle<int>>(getDrawPosition(), _objectDimensions);
        destRect->x += offset.first;
        destRect->y += offset.second;

        updatedDrawData.destinationRectangle = destRect;
        
        Services::get().getGraphics()->drawTextureCameraless(_texture, updatedDrawData);
    }

    void GUIImage::setSourceRectangle(std::shared_ptr<Rectangle<int>> sourceRectangle)
    {
        _textureDrawData.sourceRectangle = sourceRectangle;
    }

    void GUIImage::setSize(int width, int height)
    {
        _objectDimensions.first = width;
        _objectDimensions.second = height;
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

