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
        virtual ~CameraFollow();

        void setTargetPosition(const Pair<double, double> *targetPosition);

        void lockX(bool xLock);
        void lockY(bool yLock);

        void setXOffset(int xOffset);
        void setYOffset(int yOffset);
        void setOffset(int xOffset, int yOffset);

        virtual void update() override;

    private:
        const Pair<double, double> *_targetPosition;

        int _xOffset;
        int _yOffset;

        bool _xLock;
        bool _yLock;
    };

}

#endif

