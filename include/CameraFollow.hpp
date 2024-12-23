#ifndef CAMERA_FOLLOW_HPP
#define CAMERA_FOLLOW_HPP

#include "Camera.hpp"
#include "Pair.hpp"

class CameraFollow : public Camera
{
public:
    CameraFollow(const Pair<double, double> *targetPosition);
    ~CameraFollow();

    virtual void update();

private:
    const Pair<double, double> *_targetPosition;
};

#endif

