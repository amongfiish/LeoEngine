#include "LeoEngine/Controller.hpp"

namespace LeoEngine
{

    Controller::Controller(SDL_Joystick *sdlJoystick)
        : _sdlJoystick(sdlJoystick),
        _buttons(SDL_JoystickNumButtons(sdlJoystick),
                KeyState::RELEASED),
        _axes(SDL_JoystickNumAxes(sdlJoystick), 0)
    {

    }

    Controller::~Controller()
    {

    }

    void Controller::update()
    {
        for (auto button : _buttons)
        {
            if (button == KeyState::PRESSED)
            {
                button = KeyState::HELD;
            }
        }
    }

    void Controller::setButtonState(int buttonID, KeyState buttonState)
    {
        if (buttonID < 0 || buttonID >= _buttons.size())
        {
            return;
        }

        _buttons.at(buttonID) = buttonState;
    }

    void Controller::setAxisState(int axisID, int axisState)
    {
        if (axisID < 0 || axisID >= _axes.size())
        {
            return;
        }

        _axes.at(axisID) = axisState;
    }

    KeyState Controller::getButtonState(int buttonID) const
    {
        if (buttonID < 0 || buttonID >= _buttons.size())
        {
            return KeyState::RELEASED;
        }

        return _buttons.at(buttonID);
    }

    int Controller::getAxisState(int axisID) const
    {
        if (axisID < 0 || axisID >= _axes.size())
        {
            return 0;
        }

        return _axes.at(axisID);
    }

}
