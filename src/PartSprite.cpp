#include "LeoEngine\PartSprite.hpp"

namespace LeoEngine
{

    PartSprite::PartSprite()
        : _externalTransform(nullptr)
    {}

    void PartSprite::setExternalTransform(const Pair<double, double> *transform)
    {
        _externalTransform = transform;
    }

    void PartSprite::update()
    {
        if (_externalTransform != nullptr)
        {
            _sprite.setPosition(_externalTransform->first, _externalTransform->second);
        }
    }

    void PartSprite::draw()
    {
        _sprite.draw();
    }

    Sprite& PartSprite::getSprite()
    {
        return _sprite;
    }

}
