#ifndef CAMERA_MANAGER_HPP
#define CAMERA_MANAGER_HPP

#include <vector>
#include "LeoEngine/Pair.hpp"
using namespace std;

namespace LeoEngine
{

    class Camera;

    class CameraManager
    {
    public:
        CameraManager();
        ~CameraManager();

        void update();

        int addCamera(Camera *camera);

        void setCamera(int cameraID);

        void setCameraPosition(double x, double y);
        void setCameraPosition(const Pair<int, int> &position);
        void setCameraPosition(const Pair<double, double> &position);
        const Pair<double, double> &getPosition() const;

        void adjustPosition(Pair<int, int> &position);
        void adjustPosition(Pair<double, double> &position);

    private:
        Camera *_currentCamera = nullptr;
        vector<Camera *> _cameras;

        Pair<double, double> _fallbackPosition;
    };

}

#endif

