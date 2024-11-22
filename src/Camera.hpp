#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Pair.hpp"

class Camera
{
public:
    Camera() {}
    virtual ~Camera() {};

    void setPosition(double x, double y);
    void setPosition(const Pair<int, int>& position);
    void setPosition(const Pair<double, double>& position);

    const Pair<double, double>& getPosition() const;

    virtual void update() = 0;

protected:
    Pair<double, double> _position;
};

#endif

