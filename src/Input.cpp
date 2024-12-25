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

namespace LeoEngine
{

    Input::Input(Events *events)
        : _events(events),
        _mousePosition(0, 0),
        _mouseButtons(10, KeyState::RELEASED),
        _mouseWheelMotion(0, 0)
    {
        // initialize SDL joystick subsystem
        if (SDL_InitSubSystem(SDL_INIT_JOYSTICK) < 0)
        {
            throw runtime_error("Couldn't initialize SDL_JOYSTICK.");
        }

        // input event callbacks
        _events->addCallback(EventType::KEY_DOWN, bind(&Input::keyCallback, this, placeholders::_1));
        _events->addCallback(EventType::KEY_UP, bind(&Input::keyCallback, this, placeholders::_1));

        _events->addCallback(EventType::MOUSE_BUTTON_DOWN, bind(&Input::mouseCallback, this, placeholders::_1));
        _events->addCallback(EventType::MOUSE_BUTTON_UP, bind(&Input::mouseCallback, this, placeholders::_1));
        _events->addCallback(EventType::MOUSE_MOVED, bind(&Input::mouseCallback, this, placeholders::_1));
        _events->addCallback(EventType::MOUSE_WHEEL_MOVED, bind(&Input::mouseCallback, this, placeholders::_1));

        _events->addCallback(EventType::CONTROLLER_ADDED, bind(&Input::controllerCallback, this, placeholders::_1));
        _events->addCallback(EventType::CONTROLLER_REMOVED, bind(&Input::controllerCallback, this, placeholders::_1));
        _events->addCallback(EventType::CONTROLLER_BUTTON_DOWN, bind(&Input::controllerCallback, this, placeholders::_1));
        _events->addCallback(EventType::CONTROLLER_BUTTON_UP, bind(&Input::controllerCallback, this, placeholders::_1));
        _events->addCallback(EventType::CONTROLLER_JOYSTICK_MOVED, bind(&Input::controllerCallback, this, placeholders::_1));
    }

    Input::~Input()
    {
        SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
    }

    void Input::update()
    {
        for (auto idControllerPair : _controllers)
        {
            idControllerPair.second.update();
        }
    }

    KeyState Input::getKeyState(KeyCode keyCode) const
    {
        return _keyStates.at(keyCode);   
    }

    const Pair<int, int>& Input::getMousePosition() const
    {
        return _mousePosition;
    }

    KeyState Input::getMouseButtonState(int buttonID) const
    {
        return _mouseButtons.at(buttonID);
    }

    const Pair<int, int>& Input::getMouseWheelMotion() const
    {
        return _mouseWheelMotion;
    }

    KeyState Input::getControllerButtonState(SDL_JoystickID controllerID, int buttonID) const
    {
        return _controllers.at(controllerID).getButtonState(buttonID);
    }

    int Input::getControllerJoystickState(SDL_JoystickID controllerID, int axis) const
    {
        return _controllers.at(controllerID).getAxisState(axis);
    }

    void Input::keyCallback(Event *event)
    {
        switch (event->type)
        {
            case EventType::KEY_DOWN:
            {
                EventKeyDown *castEvent = dynamic_cast<EventKeyDown *>(event);
                if (_keyStates.find(castEvent->keyCode) == _keyStates.end())
                {
                    _keyStates.insert(make_pair(castEvent->keyCode, KeyState::PRESSED));
                }
                else
                {
                    _keyStates.at(castEvent->keyCode) = KeyState::PRESSED;
                }

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
                    _keyStates.at(castEvent->keyCode) = KeyState::PRESSED;
                }

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

    void Input::controllerCallback(Event *event)
    {
        switch(event->type)
        {
            case EventType::CONTROLLER_ADDED:
            {
                EventControllerAdded *castEvent = dynamic_cast<EventControllerAdded *>(event);
                SDL_Joystick *joystick = SDL_JoystickOpen(castEvent->controllerID);
                SDL_JoystickID joystickID = SDL_JoystickInstanceID(joystick);
                _controllers.emplace(make_pair(joystickID, joystick));
                break;
            }

            case EventType::CONTROLLER_REMOVED:
            {
                EventControllerRemoved *castEvent = dynamic_cast<EventControllerRemoved *>(event);
                auto idControllerPair = _controllers.find(castEvent->controllerID);
                _controllers.erase(idControllerPair);
                break;
            }

            case EventType::CONTROLLER_BUTTON_DOWN:
            {
                break;
            }

            case EventType::CONTROLLER_BUTTON_UP:
            {
                break;
            }

            case EventType::CONTROLLER_JOYSTICK_MOVED:
            {
                break;
            }

            default:
            {
                break;
            }
        }
    }

}
