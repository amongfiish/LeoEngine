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

    Pair<double, double> Controller::getLeftStickAxes(double deadzone) const
    {
        Pair<double, double> value = _axesLeftStick;
        if (abs(value.first) < deadzone)
        {
            value.first = 0;
        }
        if (abs(value.second) < deadzone)
        {
            value.second = 0;
        }
        return value;
    }

    Pair<double, double> Controller::getRightStickAxes(double deadzone) const
    {
        Pair<double, double> value = _axesRightStick;
        if (abs(value.first) < deadzone)
        {
            value.first = 0;
        }
        if (abs(value.second) < deadzone)
        {
            value.second = 0;
        }
        return value;
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
    }

    void Controller::setLeftStickAxisY(double value)
    {
        _axesLeftStick.second = value / AXIS_MAX;
    }

    void Controller::setRightStickAxisX(double value)
    {
        _axesRightStick.first = value / AXIS_MAX;
    }

    void Controller::setRightStickAxisY(double value)
    {
        _axesRightStick.second = value / AXIS_MAX;
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

