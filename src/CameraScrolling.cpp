#include "LeoEngine/CameraScrolling.hpp"

namespace LeoEngine
{

    CameraScrolling::CameraScrolling(double startX, double startY, double velocityX, double velocityY)
        : _velocity(velocityX, velocityY)
    {
        setPosition(startX, startY);
    }

    CameraScrolling::~CameraScrolling()
    {

    }

    void CameraScrolling::update()
    {
        _position.first += _velocity.first;
        _position.second += _velocity.second;
    }

}
