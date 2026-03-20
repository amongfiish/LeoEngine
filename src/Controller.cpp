#include "LeoEngine/Controller.hpp"

namespace LeoEngine
{

    Controller::Controller()
    {

    }

    Controller::~Controller()
    {

    }

    KeyState Controller::getButtonState(ControllerButton button) const
    {
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
        _buttonStates.at(button) = state;
    }

    void Controller::setLeftStickAxisX(double value)
    {
        _axesLeftStick.first = value;
    }

    void Controller::setLeftStickAxisY(double value)
    {
        _axesLeftStick.second = value;
    }

    void Controller::setRightStickAxisX(double value)
    {
        _axesRightStick.first = value;
    }

    void Controller::setRightStickAxisY(double value)
    {
        _axesRightStick.second = value;
    }

    void Controller::setLeftTriggerAxis(double value)
    {
        _axisLeftTrigger = value;
    }

    void Controller::setRightTriggerAxis(double value)
    {
        _axisRightTrigger = value;
    }

}

