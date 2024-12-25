#include "Camera.hpp"

using namespace LeoEngine;

void Camera::setPosition(double x, double y)
{
    _position.first = x;
    _position.second = y;
}

void Camera::setPosition(const Pair<int, int>& position)
{
    setPosition(position.first, position.second);
}

void Camera::setPosition(const Pair<double, double>& position)
{
    setPosition(position.first, position.second);
}

const Pair<double, double>& Camera::getPosition() const
{
    return _position;
}

