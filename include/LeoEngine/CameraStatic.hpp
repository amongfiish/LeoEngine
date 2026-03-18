#ifndef CAMERA_STATIC_HPP
#define CAMERA_STATIC_HPP

#include "LeoEngine/Camera.hpp"
#include "LeoEngine/Pair.hpp"

namespace LeoEngine
{

    class CameraStatic : public Camera
    {
    public:
        CameraStatic();
        CameraStatic(int x, int y);
        CameraStatic(Pair<int, int> &position);

        virtual ~CameraStatic();

        virtual void update();
    };

}

#endif

