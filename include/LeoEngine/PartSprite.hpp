#ifndef PART_SPRITE_HPP
#define PART_SPRITE_HPP

#include "LeoEngine\Part.hpp"
#include "LeoEngine\Pair.hpp"
#include "LeoEngine\Sprite.hpp"

namespace LeoEngine
{

    class PartSprite : public Part
    {
    public:
        PartSprite();
        virtual ~PartSprite() {};

        void setExternalTransform(const Pair<double, double> *transform);

        virtual void update() override;
        virtual void draw() override;

        Sprite& getSprite();

    private:
        const Pair<double, double> *_externalTransform;

        Sprite _sprite;
    };

}

#endif
