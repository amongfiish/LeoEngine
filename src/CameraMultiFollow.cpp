#include <cmath>
#include <string>
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Logger.hpp"
#include "LeoEngine/CameraMultiFollow.hpp"

namespace LeoEngine
{

    CameraMultiFollow::CameraMultiFollow(double baseZoom, double zoomMultiplier)
        : _nextID(0),
          _BASE_ZOOM(baseZoom),
          _ZOOM_MULTIPLIER(zoomMultiplier)
    {

    }

    int CameraMultiFollow::addTargetPosition(const Pair<double, double>* position)
    {
        _targetPositions.emplace(std::make_pair(_nextID, position));

        return _nextID++;
    }

    void CameraMultiFollow::removeTargetPosition(int i)
    {
        _targetPositions.erase(i);
    }

    void CameraMultiFollow::setOffset(Pair<double, double> offset)
    {
        _offset = offset;
    }

    void CameraMultiFollow::update()
    {
        if (_targetPositions.size() > 0)
        {
            int i = 0;
            Pair<double, double> averagePosition;
            for (auto& p : _targetPositions)
            {
                // Services::get().getLogger()->debug("CameraMultiFollow", "Position #" + std::to_string(i) + ": " + p.second->toString());
                averagePosition += *p.second;
                i++;
            }
            averagePosition /= _targetPositions.size();

            // Services::get().getLogger()->debug("CameraMultiFollow", "Average position: " + (averagePosition + _offset).toString());


            // distance between camera and any target position
            Pair<double, double> cameraDistanceComponents = averagePosition - *(_targetPositions.begin()->second);

            // Services::get().getLogger()->debug("CameraMultiFollow", "Camera distance components: " + cameraDistanceComponents.toString());

            double cameraDistance = sqrt(pow(cameraDistanceComponents.first,2) + pow(cameraDistanceComponents.second,2));
            double zoomAmount = _BASE_ZOOM + (cameraDistance * _ZOOM_MULTIPLIER);
            // Services::get().getLogger()->debug("CameraMultiFollow", "Zoom amount: " + std::to_string(zoomAmount));
            setZoom(zoomAmount, zoomAmount);

            setPosition(averagePosition + _offset/_zoom);
        }
    }

}

