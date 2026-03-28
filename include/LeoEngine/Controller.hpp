#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <map>
#include "LeoEngine/ControllerButton.hpp"
#include "LeoEngine/KeyState.hpp"
#include "LeoEngine/Pair.hpp"
#include "LeoEngine/Input.hpp"

#define AXIS_MAX 32768

namespace LeoEngine
{

    class Controller
    {
    public:
        Controller(int joystickID);
        ~Controller();

        int getJoystickID() const;

        KeyState getButtonState(ControllerButton button);

        Pair<double, double> getLeftStickAxes(double deadzone) const;
        Pair<double, double> getRightStickAxes(double deadzone) const;

        double getLeftTriggerAxis() const;
        double getRightTriggerAxis() const;

    private:
        friend Input;

        void setButtonState(ControllerButton button, KeyState state);

        void setLeftStickAxisX(double value);
        void setLeftStickAxisY(double value);

        void setRightStickAxisX(double value);
        void setRightStickAxisY(double value);

        void setLeftTriggerAxis(double value);
        void setRightTriggerAxis(double value);

        std::map<ControllerButton, KeyState> _buttonStates;
        
        Pair<double, double> _axesLeftStick;
        Pair<double, double> _axesRightStick;
        double _axisLeftTrigger;
        double _axisRightTrigger;

        int _joystickID;
        SDL_Gamepad* _gamepad;
    };

}

#endif

