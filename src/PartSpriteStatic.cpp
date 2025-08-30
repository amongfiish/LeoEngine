#include "LeoEngine/PartSpriteStatic.hpp"

namespace LeoEngine
{

    PartSpriteStatic::PartSpriteStatic()
        : _externalTransform(nullptr)
    {
        
    }

    PartSpriteStatic::~PartSpriteStatic()
    {

    }

    void PartSpriteStatic::setExternalTransform(const Pair<double, double> *transform)
    {
        _externalTransform = transform;
    }

    void PartSpriteStatic::update(double deltaTime)
    {
        if (_externalTransform != nullptr)
        {
            _sprite.setPosition(_externalTransform->first, _externalTransform->second);
        }
    }

    void PartSpriteStatic::draw()
    {
        _sprite.draw();
    }

    SpriteStatic& PartSpriteStatic::getSprite()
    {
        return _sprite;
    }

}
