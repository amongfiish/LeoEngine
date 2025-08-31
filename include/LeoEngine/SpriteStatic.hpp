#ifndef SPRITE_STATIC_HPP
#define SPRITE_STATIC_HPP

#include <string>
#include "LeoEngine/TextureDrawData.hpp"
#include "LeoEngine/Rectangle.hpp"
#include "LeoEngine/Pair.hpp"

namespace LeoEngine
{

    class SpriteStatic
    {
    public:
        SpriteStatic();
        SpriteStatic(std::string textureFilename);
        SpriteStatic(std::string textureFilename, TextureDrawData textureDrawData);

        void draw();

        const TextureDrawData *getDrawData() const;

        void setPosition(int x, int y);
        void setSize(int width, int height);

        // should this be changed so that changes are made through calls to
        // the TextureDrawData itself?
        void setSourceRectangle(std::shared_ptr<Rectangle<int>> sourceRectangle);
        void setDestinationRectangle(std::shared_ptr<Rectangle<int>> destinationRectangle);
        void setAngle(double angle);
        void setCenter(std::shared_ptr<Pair<int, int>> center);
        void setFlip(FlipType flip);

        void setTextureFilename(std::string filename);

        void setIgnoreCamera(bool value);

    private:
        std::string _textureFilename;
        TextureDrawData _textureDrawData;

        bool _ignoreCamera;
    };

}

#endif

