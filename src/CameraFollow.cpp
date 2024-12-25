#include "CameraFollow.hpp"

using namespace LeoEngine;

CameraFollow::CameraFollow(const Pair<double, double> *targetPosition)
    : _targetPosition(targetPosition)
{
    
}

CameraFollow::~CameraFollow()
{

}

void CameraFollow::update()
{
    _position.first = _targetPosition->first;
    _position.second = _targetPosition->second;
}

