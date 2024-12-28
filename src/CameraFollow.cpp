#include "LeoEngine/CameraFollow.hpp"

namespace LeoEngine
{

    CameraFollow::CameraFollow()
        : _targetPosition(nullptr),
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

    void CameraFollow::update()
    {
        if (!_targetPosition)
        {
            return;
        }

        if (!_xLock)
        {
            _position.first = _targetPosition->first;
        }
        
        if (!_yLock)
        {
            _position.second = _targetPosition->second;
        }
    }

}
