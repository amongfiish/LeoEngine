#include <iostream>
#include "LeoEngine/CameraManager.hpp"
#include "LeoEngine/Camera.hpp"
using namespace std;

namespace LeoEngine
{

    CameraManager::CameraManager()
        : _fallbackPosition()
    {

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
        return _cameras.size() - 1;
    }

    void CameraManager::setCamera(int cameraID)
    {
        _currentCamera = _cameras.at(cameraID);
        _currentCamera->update();
    }

    void CameraManager::setCameraPosition(double x, double y)
    {
        if (_currentCamera == nullptr)
        {
            return;
        }

        _currentCamera->setPosition(x, y);
    }

    void CameraManager::setCameraPosition(const Pair<int, int>& position)
    {
        if (_currentCamera == nullptr)
        {
            return;
        }

        _currentCamera->setPosition(position);
    }

    void CameraManager::setCameraPosition(const Pair<double, double>& position)
    {
        if (_currentCamera == nullptr)
        {
            return;
        }

        _currentCamera->setPosition(position);
    }

    const Pair<double, double>& CameraManager::getPosition() const
    {
        if (_currentCamera == nullptr)
        {
            return _fallbackPosition;
        }

        return _currentCamera->getPosition();
    }

    void CameraManager::adjustPosition(Pair<int, int>& position)
    {
        if (_currentCamera == nullptr)
        {
            return;
        }

        const Pair<double, double>& cameraPosition = _currentCamera->getPosition();

        position.first -= cameraPosition.first;
        position.second -= cameraPosition.second;
    }

    void CameraManager::adjustPosition(Pair<double, double>& position)
    {
        if (_currentCamera == nullptr)
        {
            return;
        }

        const Pair<double, double>& cameraPosition = _currentCamera->getPosition();

        position.first -= cameraPosition.first;
        position.second -= cameraPosition.second;
    }

}
