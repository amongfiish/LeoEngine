#ifndef CAMERA_MULTI_FOLLOW_HPP
#define CAMERA_MULTI_FOLLOW_HPP

#include <map>
#include "LeoEngine/Camera.hpp"
#include "LeoEngine/Pair.hpp"

namespace LeoEngine
{

    class CameraMultiFollow : public Camera
    {
    public:
        CameraMultiFollow(double baseZoom=1.0, double zoomMultiplier=0.0);

        int addTargetPosition(const Pair<double, double>* position);
        void removeTargetPosition(int i);

        void setOffset(Pair<double, double> offset);

        virtual void update() override;

    private:
        std::map<int, const Pair<double, double>*> _targetPositions;

        const double _BASE_ZOOM;
        const double _ZOOM_MULTIPLIER;

        Pair<double, double> _offset;

        int _nextID;
    };

}

#endif

