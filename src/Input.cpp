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
