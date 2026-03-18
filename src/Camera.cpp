#include "LeoEngine/Camera.hpp"
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Logger.hpp"

namespace LeoEngine
{

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

    void Camera::setZoom(double x, double y)
    {
        _zoom.first = x;
        _zoom.second = y;
    }

    void Camera::setZoom(const Pair<int, int>& zoom)
    {
        setZoom(zoom.first, zoom.second);
    }

    void Camera::setZoom(const Pair<double, double>& zoom)
    {
        setZoom(zoom.first, zoom.second);
    }

    const Pair<double, double>& Camera::getPosition() const
    {
        return _position;
    }

    const Pair<double, double>& Camera::getZoom() const
    {
        return _zoom;
    }

}
