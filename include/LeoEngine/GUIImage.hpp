#ifndef GUI_IMAGE_HPP
#define GUI_IMAGE_HPP

#include <memory>
#include "LeoEngine/GUIObject.hpp"
#include "LeoEngine/Texture.hpp"
#include "LeoEngine/TextureDrawData.hpp"
#include "LeoEngine/Pair.hpp"

namespace LeoEngine
{

    class GUIImage : public GUIObject
    {
    public:
        GUIImage(std::string textureFilename);
        virtual ~GUIImage();

        using GUIObject::update;
        virtual void update(Pair<int, int>& offset);
        using GUIObject::draw;
        virtual void draw(Pair<int, int>& offset);

        void setSourceRectangle(std::shared_ptr<Rectangle<int>> sourceRectangle);
        void setSize(int width, int height);
        void setAngle(double angle);
        void setCenter(std::shared_ptr<Pair<int, int>> center);
        void setFlip(FlipType flip);

    private:
        Texture& _texture;
        TextureDrawData _textureDrawData;
    };

}

#endif

