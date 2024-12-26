#ifndef CAMERA_SCROLLING_HPP
#define CAMERA_SCROLLING_HPP

#include "LeoEngine/Camera.hpp"

namespace LeoEngine
{

    class CameraScrolling : public Camera
    {
    public:
        CameraScrolling(double startX, double startY, double velocityX, double velocityY);
        ~CameraScrolling();

        virtual void update();

    private:
        Pair<double, double> _velocity;
    };

}

#endif

