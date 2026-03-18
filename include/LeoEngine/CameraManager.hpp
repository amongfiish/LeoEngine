#ifndef CAMERA_MANAGER_HPP
#define CAMERA_MANAGER_HPP

#include <vector>
#include "LeoEngine/Pair.hpp"
#include "LeoEngine/Rectangle.hpp"

namespace LeoEngine
{

    class Camera;

    class CameraManager
    {
    public:
        CameraManager();
        ~CameraManager();

        void update();

        bool currentCameraExists();

        // change to be more like scene stuff?
        int addCamera(Camera *camera);

        void setCamera(int cameraID);

        void setCameraPosition(double x, double y);
        void setCameraPosition(const Pair<int, int>& position);
        void setCameraPosition(const Pair<double, double>& position);

        void setCameraZoom(double x, double y);
        void setCameraZoom(const Pair<int, int>& zoom);
        void setCameraZoom(const Pair<double, double>& zoom);

        const Pair<double, double>& getPosition() const;

        const Pair<double, double>& getZoom() const;

        void adjustPosition(Pair<double, double> &position);
        void adjustRectangle(Rectangle<double>& rectangle);

    private:
        Camera *_currentCamera;
        std::vector<Camera *> _cameras;
    };

}

#endif

