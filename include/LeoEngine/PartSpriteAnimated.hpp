#ifndef PART_SPRITE_ANIMATED_HPP
#define PART_SPRITE_ANIMATED_HPP

#include "LeoEngine/Part.hpp"
#include "LeoEngine/Pair.hpp"
#include "LeoEngine/SpriteAnimated.hpp"

namespace LeoEngine
{

    class PartSpriteAnimated : public Part
    {
    public:
        PartSpriteAnimated();
        virtual ~PartSpriteAnimated();

        void setExternalTransform(const Pair<double, double> *transform);

        virtual void update(double deltaTime) override;
        virtual void draw() override;

        SpriteAnimated &getSprite();

    private:
        const Pair<double, double> *_externalTransform;

        SpriteAnimated _sprite;
    };

}

#endif
