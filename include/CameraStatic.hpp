#ifndef CAMERA_STATIC_HPP
#define CAMERA_STATIC_HPP

#include "Camera.hpp"
#include "Pair.hpp"

class CameraStatic : public Camera
{
public:
    CameraStatic(int x, int y);
    CameraStatic(Pair<int, int>& position);

    virtual ~CameraStatic();

    virtual void update();
};

#endif

