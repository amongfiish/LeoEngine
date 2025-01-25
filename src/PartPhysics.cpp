#include "LeoEngine/PartPhysics.hpp"

namespace LeoEngine
{

    PartPhysics::PartPhysics()
        : _velocity(0, 0),
        _target(nullptr),
        _acceleration(0, 0)
    {

    }

    PartPhysics::~PartPhysics()
    {

    }

    void PartPhysics::setTarget(std::shared_ptr<PartTransform> target)
    {
        _target = target;
    }

    void PartPhysics::setVelocity(double x, double y)
    {
        _velocity.first = x;
        _velocity.second = y;
    }

    void PartPhysics::setVelocity(const Pair<double, double> &velocity)
    {
        setVelocity(velocity.first, velocity.second);
    }

    const Pair<double, double> &PartPhysics::getVelocity()
    {
        return _velocity;
    }

    void PartPhysics::setAcceleration(double x, double y)
    {
        _acceleration.first = x;
        _acceleration.second = y;
    }

    void PartPhysics::setAcceleration(const Pair<double, double> &acceleration)
    {
        setAcceleration(acceleration.first, acceleration.second);
    }

    const Pair<double, double> &PartPhysics::getAcceleration()
    {
        return _acceleration;
    }

    bool PartPhysics::isInMotion()
    {
        return _velocity.first != 0 || _velocity.second != 0;
    }

    void PartPhysics::update()
    {
        if (_target == nullptr)
        {
            return;
        }

        _velocity.first += _acceleration.first;
        _velocity.second += _acceleration.second;

        _target->move(_velocity);
    }

}
