#include "LeoEngine/PartSpriteAnimated.hpp"

namespace LeoEngine
{

    PartSpriteAnimated::PartSpriteAnimated()
        : _externalTransform(nullptr)
    {

    }

    PartSpriteAnimated::~PartSpriteAnimated()
    {

    }

    void PartSpriteAnimated::setExternalTransform(const Pair<double, double> *transform)
    {
        _externalTransform = transform;
    }

    void PartSpriteAnimated::update(double deltaTime)
    {
        _sprite.update(deltaTime);

        if (_externalTransform != nullptr)
        {
            _sprite.getSprite().setPosition(_externalTransform->first, _externalTransform->second);
        }
    }

    void PartSpriteAnimated::draw()
    {
        _sprite.draw();
    }

    SpriteAnimated &PartSpriteAnimated::getSprite()
    {
        return _sprite;
    }

}
