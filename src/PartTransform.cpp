#include "LeoEngine/PartTransform.hpp"

namespace LeoEngine
{

    PartTransform::PartTransform()
        : _position(0, 0)
    {

    }

    PartTransform::~PartTransform()
    {

    }

    const Pair<double, double>& PartTransform::getPosition() const
    {
        return _position;
    }

    void PartTransform::setPosition(double x, double y)
    {
        _position.first = x;
        _position.second = y;
    }

    void PartTransform::setPosition(const Pair<double, double>& position)
    {
        setPosition(position.first, position.second);
    }

    void PartTransform::move(double deltaX, double deltaY)
    {
        _position.first += deltaX;
        _position.second += deltaY;
    }

    void PartTransform::move(const Pair<double, double>& delta)
    {
        move(delta.first, delta.second);
    }

}
