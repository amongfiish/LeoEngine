#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "LeoEngine/Pair.hpp"

namespace LeoEngine
{

    class Camera
    {
    public:
        Camera()
            : _position(0.0, 0.0),
              _zoom(1.0, 1.0)
        {

        }

        virtual ~Camera()
        {

        };

        void setPosition(double x, double y);
        void setPosition(const Pair<int, int> &position);
        void setPosition(const Pair<double, double> &position);

        void setZoom(double x, double y);
        void setZoom(const Pair<int, int> &zoom);
        void setZoom(const Pair<double, double> &zoom);

        const Pair<double, double> &getPosition() const;

        const Pair<double, double> &getZoom() const;

        virtual void update() = 0;

    protected:
        Pair<double, double> _position;
        Pair<double, double> _zoom;
    };

}

#endif

