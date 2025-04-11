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
        GUIImage(Texture *texture);
        virtual ~GUIImage();

        virtual void update(Pair<int, int>& offset);
        virtual void draw(Pair<int, int>& offset);

        void setSourceRectangle(std::shared_ptr<Rectangle> sourceRectangle);
        void setDestinationRectangle(std::shared_ptr<Rectangle> destinationRectangle);
        void setAngle(double angle);
        void setCenter(std::shared_ptr<Pair<int, int>> center);
        void setFlip(FlipType flip);

    private:
        Texture *_texture;
        TextureDrawData _textureDrawData;
    };

}

#endif

