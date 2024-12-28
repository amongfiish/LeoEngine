#ifndef CAMERA_FOLLOW_HPP
#define CAMERA_FOLLOW_HPP

#include "LeoEngine/Camera.hpp"
#include "LeoEngine/Pair.hpp"

namespace LeoEngine
{

    class CameraFollow : public Camera
    {
    public:
        CameraFollow();
        ~CameraFollow();

        void setTargetPosition(const Pair<double, double> *targetPosition);

        void lockX(bool xLock);
        void lockY(bool yLock);

        virtual void update();

    private:
        const Pair<double, double> *_targetPosition;

        bool _xLock;
        bool _yLock;
    };

}

#endif

