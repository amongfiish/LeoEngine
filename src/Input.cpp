#include <stdexcept>
#include "LeoEngine/Input.hpp"
#include "LeoEngine/EventKeyDown.hpp"
#include "LeoEngine/EventKeyUp.hpp"
#include "LeoEngine/EventMouseButtonDown.hpp"
#include "LeoEngine/EventMouseButtonUp.hpp"
#include "LeoEngine/EventMouseMoved.hpp"
#include "LeoEngine/EventMouseWheelMoved.hpp"
#include "LeoEngine/EventControllerAdded.hpp"
#include "LeoEngine/EventControllerRemoved.hpp"
#include "LeoEngine/EventControllerJoystickMoved.hpp"
#include "LeoEngine/EventControllerButtonDown.hpp"
#include "LeoEngine/EventControllerButtonUp.hpp"
#include "LeoEngine/Controller.hpp"
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Logger.hpp"

namespace LeoEngine
{

    Input::Input(Events *events)
        : _events(events),
        _mousePosition(0, 0),
        _mouseButtons(10, KeyState::RELEASED),
        _mouseWheelMotion(0, 0),
        _locked(false)
    {
        // input event callbacks
        _events->addCallback(EventType::KEY_DOWN, bind(&Input::keyCallback, this, placeholders::_1));
        _events->addCallback(EventType::KEY_UP, bind(&Input::keyCallback, this, placeholders::_1));

        _events->addCallback(EventType::MOUSE_BUTTON_DOWN, bind(&Input::mouseCallback, this, placeholders::_1));
        _events->addCallback(EventType::MOUSE_BUTTON_UP, bind(&Input::mouseCallback, this, placeholders::_1));
        _events->addCallback(EventType::MOUSE_MOVED, bind(&Input::mouseCallback, this, placeholders::_1));
        _events->addCallback(EventType::MOUSE_WHEEL_MOVED, bind(&Input::mouseCallback, this, placeholders::_1));

        _events->addCallback(EventType::CONTROLLER_ADDED, bind(&Input::keyCallback, this, placeholders::_1));
        _events->addCallback(EventType::CONTROLLER_REMOVED, bind(&Input::keyCallback, this, placeholders::_1));
        _events->addCallback(EventType::CONTROLLER_JOYSTICK_MOVED, bind(&Input::keyCallback, this, placeholders::_1));
        _events->addCallback(EventType::CONTROLLER_BUTTON_DOWN, bind(&Input::keyCallback, this, placeholders::_1));
        _events->addCallback(EventType::CONTROLLER_BUTTON_UP, bind(&Input::keyCallback, this, placeholders::_1));
    }

    Input::~Input()
    {

    }

    void Input::update()
    {
        for (auto itKey = _keyStates.begin(); itKey != _keyStates.end(); itKey++)
        {
            if (itKey->second == KeyState::PRESSED)
            {
                itKey->second = KeyState::HELD;
            }
        }

        for (auto& c : _controllers)
        {
            for (auto itButton = c.second->_buttonStates.begin(); itButton != c.second->_buttonStates.end(); itButton++)
            {
                if (itButton->second == KeyState::PRESSED)
                {
                    itButton->second = KeyState::HELD;
                }
            }
        }

        for (auto itButton = _mouseButtons.begin(); itButton != _mouseButtons.end(); itButton++)
        {
            if (*itButton == KeyState::PRESSED)
            {
                *itButton = KeyState::HELD;
            }
        }
    }

    void Input::lockInput()
    {
        _locked = true;
    }

    void Input::unlockInput()
    {
        _locked = false;
    }

    KeyState Input::getKeyState(KeyCode keyCode) const
    {
        if (_locked)
        {
            return KeyState::RELEASED;
        }

        auto foundKeyState = _keyStates.find(keyCode);
        if (foundKeyState != _keyStates.end())
        {
            return foundKeyState->second;
        }

        return KeyState::RELEASED;
    }

    std::string Input::getKeyName(KeyCode keyCode) const
    {
        const char * sdlKeyName = SDL_GetKeyName(static_cast<SDL_Keycode>(keyCode));

        std::string keyName(sdlKeyName);
        return keyName;
    }

    const Pair<int, int>& Input::getMousePosition() const
    {
        return _mousePosition;
    }

    KeyState Input::getMouseButtonState(int buttonID) const
    {
        if (_locked)
        {
            return KeyState::RELEASED;
        }

        return _mouseButtons.at(buttonID);
    }

    const Pair<int, int>& Input::getMouseWheelMotion() const
    {
        return _mouseWheelMotion;
    }

    KeyState Input::getControllerButtonState(int controllerID, ControllerButton button) const
    {
        return _controllers.at(controllerID)->getButtonState(button);
    }

    const Pair<double, double>& Input::getControllerLeftJoystickAxes(int controllerID) const
    {
        return _controllers.at(controllerID)->getLeftStickAxes();
    }

    const Pair<double, double>& Input::getControllerRightJoystickAxes(int controllerID) const
    {
        return _controllers.at(controllerID)->getRightStickAxes();
    }

    double Input::getControllerLeftTriggerAxis(int controllerID) const
    {
        return _controllers.at(controllerID)->getLeftTriggerAxis();
    }

    double Input::getControllerRightTriggerAxis(int controllerID) const
    {
        return _controllers.at(controllerID)->getRightTriggerAxis();
    }

    void Input::keyCallback(Event *event)
    {
        switch (event->type)
        {
            case EventType::KEY_DOWN:
            {
                EventKeyDown *castEvent = dynamic_cast<EventKeyDown *>(event);
                if (castEvent->isRepeat)
                {
                    break;
                }

                if (_keyStates.find(castEvent->keyCode) == _keyStates.end())
                {
                    _keyStates.insert(make_pair(castEvent->keyCode, KeyState::PRESSED));
                }
                else
                {
                    _keyStates.at(castEvent->keyCode) = KeyState::PRESSED;
                }

                std::string traceMessage = "Key '" + getKeyName(castEvent->keyCode) + "' pressed down.";
                LeoEngine::Services::get().getLogger()->trace("Input", traceMessage);

                break;
            }

            case EventType::KEY_UP:
            {
                EventKeyUp *castEvent = dynamic_cast<EventKeyUp *>(event);
                if (_keyStates.find(castEvent->keyCode) == _keyStates.end())
                {
                    _keyStates.insert(make_pair(castEvent->keyCode, KeyState::RELEASED));
                }
                else
                {
                    _keyStates.at(castEvent->keyCode) = KeyState::RELEASED;
                }

                std::string traceMessage = "Key '" + getKeyName(castEvent->keyCode) + "' released.";
                LeoEngine::Services::get().getLogger()->trace("Input", traceMessage);

                break;
            }

            default:
            {
                break;
            }
        }
    }

    void Input::controllerCallback(Event *event)
    {
        switch(event->type)
        {
            case EventType::CONTROLLER_ADDED:
            {
                EventControllerAdded* castEvent = dynamic_cast<EventControllerAdded*>(event);
                _controllers.emplace(std::make_pair(static_cast<int>(castEvent->controllerID), new Controller));
                break;
            }

            case EventType::CONTROLLER_REMOVED:
            {
                EventControllerRemoved* castEvent = dynamic_cast<EventControllerRemoved*>(event);
                _controllers.erase(static_cast<int>(castEvent->controllerID));
                break;
            }

            case EventType::CONTROLLER_JOYSTICK_MOVED:
            {
                EventControllerJoystickMoved* castEvent = dynamic_cast<EventControllerJoystickMoved*>(event);

                switch(castEvent->axis)
                {
                case SDL_GAMEPAD_AXIS_LEFTX:
                    _controllers.at(castEvent->controllerID)->setLeftStickAxisX(castEvent->value);
                    break;

                case SDL_GAMEPAD_AXIS_LEFTY:
                    _controllers.at(castEvent->controllerID)->setLeftStickAxisY(castEvent->value);
                    break;

                case SDL_GAMEPAD_AXIS_RIGHTX:
                    _controllers.at(castEvent->controllerID)->setRightStickAxisX(castEvent->value);
                    break;

                case SDL_GAMEPAD_AXIS_RIGHTY:
                    _controllers.at(castEvent->controllerID)->setRightStickAxisY(castEvent->value);
                    break;

                case SDL_GAMEPAD_AXIS_LEFT_TRIGGER:
                    _controllers.at(castEvent->controllerID)->setLeftTriggerAxis(castEvent->value);
                    break;

                case SDL_GAMEPAD_AXIS_RIGHT_TRIGGER:
                    _controllers.at(castEvent->controllerID)->setRightTriggerAxis(castEvent->value);
                    break;
                }
                break;
            }

            case EventType::CONTROLLER_BUTTON_DOWN:
            {
                EventControllerButtonDown* castEvent = dynamic_cast<EventControllerButtonDown*>(event);
                _controllers.at(castEvent->controllerID)->setButtonState(castEvent->button, KeyState::PRESSED);
                break;
            }

            case EventType::CONTROLLER_BUTTON_UP:
            {
                EventControllerButtonUp* castEvent = dynamic_cast<EventControllerButtonUp*>(event);
                _controllers.at(castEvent->controllerID)->setButtonState(castEvent->button, KeyState::RELEASED);
                break;
            }

            default:
            {
                break;
            }
        }
    }

    void Input::mouseCallback(Event *event)
    {
        switch(event->type)
        {
            case EventType::MOUSE_BUTTON_DOWN:
            {
                EventMouseButtonDown *castEvent = dynamic_cast<EventMouseButtonDown *>(event);
                _mouseButtons.at(castEvent->mouseButton) = KeyState::PRESSED;
                break;
            }

            case EventType::MOUSE_BUTTON_UP:
            {
                EventMouseButtonUp *castEvent = dynamic_cast<EventMouseButtonUp *>(event);
                _mouseButtons.at(castEvent->mouseButton) = KeyState::RELEASED;
                break;
            }

            case EventType::MOUSE_MOVED:
            {
                EventMouseMoved *castEvent = dynamic_cast<EventMouseMoved *>(event);
                _mousePosition.first = castEvent->x;
                _mousePosition.second = castEvent->y;
                break;
            }

            case EventType::MOUSE_WHEEL_MOVED:
            {
                EventMouseWheelMoved *castEvent = dynamic_cast<EventMouseWheelMoved *>(event);
                _mouseWheelMotion.first = castEvent->x;
                _mouseWheelMotion.second = castEvent->y;
                break;
            }

            default:
            {
                break;
            }
        }
    }

}
