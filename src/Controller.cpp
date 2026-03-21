#include "LeoEngine/Controller.hpp"
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Logger.hpp"

namespace LeoEngine
{

    Controller::Controller(int joystickID)
    {
        _gamepad = SDL_OpenGamepad(joystickID);
        _joystickID = SDL_GetGamepadID(_gamepad);
    }

    Controller::~Controller()
    {
        SDL_CloseGamepad(_gamepad);
    }

    int Controller::getJoystickID() const
    {
        return _joystickID;
    }

    KeyState Controller::getButtonState(ControllerButton button)
    {
        if (_buttonStates.find(button) == _buttonStates.end())
        {
            _buttonStates[button] = KeyState::RELEASED;
        }

        return _buttonStates.at(button);
    }

    const Pair<double, double>& Controller::getLeftStickAxes() const
    {
        return _axesLeftStick;
    }

    const Pair<double, double>& Controller::getRightStickAxes() const
    {
        return _axesRightStick;
    }

    double Controller::getLeftTriggerAxis() const
    {
        return _axisLeftTrigger;
    }

    double Controller::getRightTriggerAxis() const
    {
        return _axisRightTrigger;
    }

    void Controller::setButtonState(ControllerButton button, KeyState state)
    {
        _buttonStates[button] = state;
    }

    void Controller::setLeftStickAxisX(double value)
    {
        _axesLeftStick.first = value / AXIS_MAX;
        if (abs(_axesLeftStick.first) < DEADZONE)
        {
            _axesLeftStick.first = 0;
        }
    }

    void Controller::setLeftStickAxisY(double value)
    {
        _axesLeftStick.second = value / AXIS_MAX;
        if (abs(_axesLeftStick.second) < DEADZONE)
        {
            _axesLeftStick.second = 0;
        }
    }

    void Controller::setRightStickAxisX(double value)
    {
        _axesRightStick.first = value / AXIS_MAX;
        if (abs(_axesRightStick.first) < DEADZONE)
        {
            _axesRightStick.first = 0;
        }
    }

    void Controller::setRightStickAxisY(double value)
    {
        _axesRightStick.second = value / AXIS_MAX;
        if (abs(_axesRightStick.second) < DEADZONE)
        {
            _axesRightStick.second = 0;
        }
    }

    void Controller::setLeftTriggerAxis(double value)
    {
        _axisLeftTrigger = value / AXIS_MAX;
    }

    void Controller::setRightTriggerAxis(double value)
    {
        _axisRightTrigger = value / AXIS_MAX;
    }

}

