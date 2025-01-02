#ifndef PART_SPRITE_STATIC_HPP
#define PART_SPRITE_STATIC_HPP

#include "LeoEngine/Part.hpp"
#include "LeoEngine/Pair.hpp"
#include "LeoEngine/SpriteStatic.hpp"

namespace LeoEngine
{

    class PartSpriteStatic : public Part
    {
    public:
        PartSpriteStatic();
        virtual ~PartSpriteStatic();

        void setExternalTransform(const Pair<double, double> *transform);

        virtual void update() override;
        virtual void draw() override;

        SpriteStatic& getSprite();

    private:
        const Pair<double, double> *_externalTransform;

        SpriteStatic _sprite;
    };

}

#endif
