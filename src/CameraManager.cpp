#include <iostream>
#include "LeoEngine/CameraManager.hpp"
#include "LeoEngine/Camera.hpp"
#include "LeoEngine/CameraStatic.hpp"
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Logger.hpp"
using namespace std;

namespace LeoEngine
{

    CameraManager::CameraManager()
    {
        addCamera(new CameraStatic);
        setCamera(0);
    }

    CameraManager::~CameraManager()
    {
        for (auto camera : _cameras)
        {
            delete camera;
        }
    }

    void CameraManager::update()
    {
        if (_currentCamera == nullptr)
        {
            return;
        }

        _currentCamera->update();
    }

    bool CameraManager::currentCameraExists()
    {
        return _currentCamera != nullptr;
    }

    int CameraManager::addCamera(Camera *camera)
    {
        _cameras.push_back(camera);
        return static_cast<int>(_cameras.size()) - 1;
    }

    void CameraManager::setCamera(int cameraID)
    {
        _currentCamera = _cameras.at(cameraID);
        _currentCamera->update();
    }

    void CameraManager::setCameraPosition(double x, double y)
    {
        _currentCamera->setPosition(x, y);
    }

    void CameraManager::setCameraPosition(const Pair<int, int>& position)
    {
        _currentCamera->setPosition(position);
    }

    void CameraManager::setCameraPosition(const Pair<double, double>& position)
    {
        _currentCamera->setPosition(position);
    }

    void CameraManager::setCameraZoom(double x, double y)
    {
        _currentCamera->setZoom(x, y);
    }

    void CameraManager::setCameraZoom(const Pair<int, int>& zoom)
    {
        _currentCamera->setZoom(zoom);
    }

    void CameraManager::setCameraZoom(const Pair<double, double>& zoom)
    {
        _currentCamera->setZoom(zoom);
    }

    const Pair<double, double>& CameraManager::getPosition() const
    {
        return _currentCamera->getPosition();
    }

    const Pair<double, double>& CameraManager::getZoom() const
    {
        return _currentCamera->getZoom();
    }

    void CameraManager::adjustPosition(Pair<double, double>& position)
    {
        const Pair<double, double>& cameraPosition = getPosition();
        const Pair<double, double>& zoomFactor = getZoom();

        Pair<double, double> scaledRelativePosition = (position - cameraPosition) * zoomFactor;
        
        position = scaledRelativePosition;
    }

    void CameraManager::adjustRectangle(Rectangle<double>& rectangle)
    {
        const Pair<double, double>& cameraPosition = getPosition();
        const Pair<double, double>& zoomFactor = getZoom();

        Pair<double, double> position(rectangle.x, rectangle.y);

        // LeoEngine::Services::get().getLogger()->debug("CameraManager", "Position: " + position.toString());

        Pair<double, double> scaledRelativePosition = (position - cameraPosition) * zoomFactor;

        // LeoEngine::Services::get().getLogger()->debug("CameraManager", "Scaled relative position: " + scaledRelativePosition.toString());

        rectangle.x = scaledRelativePosition.first;
        rectangle.y = scaledRelativePosition.second;
        rectangle.width *= zoomFactor.first;
        rectangle.height *= zoomFactor.second;
    }

}

