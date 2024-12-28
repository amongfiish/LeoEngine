#include "LeoEngine/CameraFollow.hpp"

namespace LeoEngine
{

    CameraFollow::CameraFollow()
        : _targetPosition(nullptr),
          _xOffset(0),
          _yOffset(0),
          _xLock(false),
          _yLock(false)
    {}

    CameraFollow::~CameraFollow()
    {}

    void CameraFollow::setTargetPosition(const Pair<double, double> *targetPosition)
    {
        _targetPosition = targetPosition;
    }

    void CameraFollow::lockX(bool xLock)
    {
        _xLock = xLock;
    }

    void CameraFollow::lockY(bool yLock)
    {
        _yLock = yLock;
    }

    void CameraFollow::setXOffset(int xOffset)
    {
        _xOffset = xOffset;
    }

    void CameraFollow::setYOffset(int yOffset)
    {
        _yOffset = yOffset;
    }

    void CameraFollow::setOffset(int xOffset, int yOffset)
    {
        setXOffset(xOffset);
        setYOffset(yOffset);
    }

    void CameraFollow::update()
    {
        if (!_targetPosition)
        {
            return;
        }

        if (!_xLock)
        {
            _position.first = _targetPosition->first + _xOffset;
        }
        
        if (!_yLock)
        {
            _position.second = _targetPosition->second + _yOffset;
        }
    }

}
