#include <stdexcept>
#include "LeoEngine/Input.hpp"
#include "LeoEngine/UIButton.hpp"
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
#include "LeoEngine/Colour.hpp"
#include "LeoEngine/Controller.hpp"
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Logger.hpp"
#include "LeoEngine/Graphics.hpp"

namespace LeoEngine
{

    Input::Input(Events *events)
        : _events(events),
        _mousePosition(0, 0),
        _mouseButtons(10, KeyState::RELEASED),
        _mouseWheelMotion(0, 0),
        _locked(false),
        _lastAddedControllerID(-1)
    {
        // input event callbacks
        _events->addCallback(EventType::KEY_DOWN, bind(&Input::keyCallback, this, placeholders::_1));
        _events->addCallback(EventType::KEY_UP, bind(&Input::keyCallback, this, placeholders::_1));

        _events->addCallback(EventType::MOUSE_BUTTON_DOWN, bind(&Input::mouseCallback, this, placeholders::_1));
        _events->addCallback(EventType::MOUSE_BUTTON_UP, bind(&Input::mouseCallback, this, placeholders::_1));
        _events->addCallback(EventType::MOUSE_MOVED, bind(&Input::mouseCallback, this, placeholders::_1));
        _events->addCallback(EventType::MOUSE_WHEEL_MOVED, bind(&Input::mouseCallback, this, placeholders::_1));

        _events->addCallback(EventType::CONTROLLER_ADDED, bind(&Input::controllerCallback, this, placeholders::_1));
        _events->addCallback(EventType::CONTROLLER_REMOVED, bind(&Input::controllerCallback, this, placeholders::_1));
        _events->addCallback(EventType::CONTROLLER_JOYSTICK_MOVED, bind(&Input::controllerCallback, this, placeholders::_1));
        _events->addCallback(EventType::CONTROLLER_BUTTON_DOWN, bind(&Input::controllerCallback, this, placeholders::_1));
        _events->addCallback(EventType::CONTROLLER_BUTTON_UP, bind(&Input::controllerCallback, this, placeholders::_1));

        for (int i = 0; i < MAX_CONTROLLERS; i++)
        {
            _playerAssignedControllerIDs[i] = -1;
        }
    }

    Input::~Input()
    {
        for (auto& p : _controllers)
        {
            delete p.second;
        }
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

    void Input::draw()
    {
        static const Colour CURSOR_COLOUR(0xFF, 0xFF, 0xFF, 0xFF);

        if (_controllerCursorSelection == nullptr)
        {
            return;
        }

        LeoEngine::Rectangle<int> cursorBounds = _controllerCursorSelection->getGlobalBounds();
        cursorBounds.x -= 1;
        cursorBounds.y -= 1;
        cursorBounds.width += 2;
        cursorBounds.height += 2;

        LeoEngine::Services::get().getGraphics()->drawRectangleCameraless(CURSOR_COLOUR, false, cursorBounds);
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

    Pair<int, int> Input::getMousePosition() const
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

    Pair<int, int> Input::getMouseWheelMotion() const
    {
        if (_locked)
        {
            return Pair<int, int>(0, 0);
        }

        return _mouseWheelMotion;
    }

    std::vector<int> Input::getConnectedControllers() const
    {
        std::vector<int> connectedControllers;
        for (auto it = _controllers.begin(); it != _controllers.end(); it++)
        {
            connectedControllers.push_back(it->first);   
        }

        return connectedControllers;
    }

    bool Input::controllerExists(int controllerID) const
    {
        if (_controllers.find(controllerID) == _controllers.end())
        {
            return false;
        }

        return true;
    }

    int Input::getLastAddedControllerID() const
    {
        return _lastAddedControllerID;
    }

    void Input::setPlayerControllerID(int player, int id)
    {
        if (player < 0 || player >= MAX_CONTROLLERS)
        {
            std::string errorMessage = "Player ID (" + std::to_string(player) + ") is out of range: [0, " + std::to_string(MAX_CONTROLLERS) + "].";
            LeoEngine::Services::get().getLogger()->error("Input", errorMessage);
            LeoEngine::Services::get().getLogger()->flush();
            throw std::runtime_error(errorMessage);
        }

        if (!controllerExists(id))
        {
            std::string errorMessage = "Controller (ID: " + std::to_string(id) + ") does not exist.";
            LeoEngine::Services::get().getLogger()->error("Input", errorMessage);
            LeoEngine::Services::get().getLogger()->flush();
            throw std::runtime_error(errorMessage);
        }

        _playerAssignedControllerIDs[player] = id;

        Services::get().getLogger()->info("Input", "Controller (ID: " + std::to_string(id) + ") assigned to player #" + std::to_string(player) + ".");
    }

    int Input::getControllerIDByPlayer(int player) const
    {
        if (player < 0 || player >= MAX_CONTROLLERS)
        {
            std::string errorMessage = "Player ID (" + std::to_string(player) + ") is out of range: [0, " + std::to_string(MAX_CONTROLLERS) + "].";
            LeoEngine::Services::get().getLogger()->error("Input", errorMessage);
            LeoEngine::Services::get().getLogger()->flush();
            throw std::runtime_error(errorMessage);
        }

        return _playerAssignedControllerIDs[player];
    }

    int Input::getPlayerByControllerID(int id) const
    {
        for (int i = 0; i < MAX_CONTROLLERS; i++)
        {
            if (_playerAssignedControllerIDs[i] == id)
            {
                return i;
            }
        }

        return -1;
    }

    KeyState Input::getControllerButtonState(int controllerID, ControllerButton button) const
    {
        if (!controllerExists(controllerID))
        {
            std::string errorMessage = "Cannot get button state from controllerID #" + std::to_string(controllerID) + " (does not exist).";
            Services::get().getLogger()->error("Input", errorMessage);
            Services::get().getLogger()->flush();
            throw std::runtime_error(errorMessage);
        }

        if (_locked)
        {
            return KeyState::RELEASED;
        }

        std::map<ControllerButton, KeyState> buttonStates = _controllers.at(controllerID)->_buttonStates;

        auto foundButtonState = buttonStates.find(button);
        if (foundButtonState != buttonStates.end())
        {
            return foundButtonState->second;
        }

        return _controllers.at(controllerID)->getButtonState(button);
    }

    Pair<double, double> Input::getControllerLeftJoystickAxes(int controllerID) const
    {
        if (!controllerExists(controllerID))
        {
            std::string errorMessage = "Cannot get controller left joystick axes from controllerID #" + std::to_string(controllerID) + " (does not exist).";
            Services::get().getLogger()->error("Input", errorMessage);
            throw std::runtime_error(errorMessage);
        }

        if (_locked)
        {
            return Pair<double, double>(0.0, 0.0);
        }

        return _controllers.at(controllerID)->getLeftStickAxes();
    }

    Pair<double, double> Input::getControllerRightJoystickAxes(int controllerID) const
    {
        if (!controllerExists(controllerID))
        {
            std::string errorMessage = "Cannot get controller right joystick axes from controllerID #" + std::to_string(controllerID) + " (does not exist).";
            Services::get().getLogger()->error("Input", errorMessage);
            throw std::runtime_error(errorMessage);
        }

        if (_locked)
        {
            return Pair<double, double>(0.0, 0.0);
        }

        return _controllers.at(controllerID)->getRightStickAxes();
    }

    double Input::getControllerLeftTriggerAxis(int controllerID) const
    {
        if (!controllerExists(controllerID))
        {
            std::string errorMessage = "Cannot get controller left trigger axes from controllerID #" + std::to_string(controllerID) + " (does not exist).";
            Services::get().getLogger()->error("Input", errorMessage);
            throw std::runtime_error(errorMessage);
        }

        if (_locked)
        {
            return 0;
        }

        return _controllers.at(controllerID)->getLeftTriggerAxis();
    }

    double Input::getControllerRightTriggerAxis(int controllerID) const
    {
        if (!controllerExists(controllerID))
        {
            std::string errorMessage = "Cannot get controller right trigger axes from controllerID #" + std::to_string(controllerID) + " (does not exist).";
            Services::get().getLogger()->error("Input", errorMessage);
            throw std::runtime_error(errorMessage);
        }

        if (_locked)
        {
            return 0;
        }

        return _controllers.at(controllerID)->getRightTriggerAxis();
    }

    void Input::registerControllerCursorDefaultSelection(UIButton* button)
    {
        if (button == nullptr)
        {
            _controllerCursorSelection = nullptr;
        }

        _controllerCursorDefaultSelection = button;
    }

    void Input::_handleCursorMove(KeyCode direction)
    {
        if (_controllerCursorSelection == nullptr)
        {
            _controllerCursorSelection = _controllerCursorDefaultSelection;
            return;
        }

        UIButton* nextSelection = nullptr;

        switch (direction)
        {
        case KeyCode::LEFT_ARROW:
            nextSelection = _controllerCursorSelection->getLeftButton();
            break;

        case KeyCode::RIGHT_ARROW:
            nextSelection = _controllerCursorSelection->getRightButton();
            break;

        case KeyCode::UP_ARROW:
            nextSelection = _controllerCursorSelection->getUpButton();
            break;

        case KeyCode::DOWN_ARROW:
            nextSelection = _controllerCursorSelection->getDownButton();
            break;

        default:
            break;
        }

        if (nextSelection == nullptr)
        {
            return;
        }

        _controllerCursorSelection = nextSelection;
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
                Services::get().getLogger()->trace("Input", traceMessage);

                // controllerButtonSelection
                switch (castEvent->keyCode)
                {
                case KeyCode::LEFT_ARROW:
                    _handleCursorMove(KeyCode::LEFT_ARROW);
                    break;

                case KeyCode::RIGHT_ARROW:
                    _handleCursorMove(KeyCode::RIGHT_ARROW);
                    break;

                case KeyCode::UP_ARROW:
                    _handleCursorMove(KeyCode::UP_ARROW);
                    break;

                case KeyCode::DOWN_ARROW:
                    _handleCursorMove(KeyCode::DOWN_ARROW);
                    break;

                case KeyCode::SPACE:
                    if (_controllerCursorSelection != nullptr)
                    {
                        _controllerCursorSelection->click();
                        if (_controllerCursorSelection && _controllerCursorSelection->getUnhoverOnClick())
                        {
                            _controllerCursorSelection = nullptr;
                        }
                    }
                    break;

                default:
                    break;
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
                    _keyStates.at(castEvent->keyCode) = KeyState::RELEASED;
                }

                std::string traceMessage = "Key '" + getKeyName(castEvent->keyCode) + "' released.";
                Services::get().getLogger()->trace("Input", traceMessage);

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
                Controller* newController = new Controller(castEvent->controllerID);
                _controllers.emplace(std::make_pair(newController->getJoystickID(), newController));
                _lastAddedControllerID = newController->getJoystickID();

                Services::get().getLogger()->info("Input", "Controller connected (ID: " + std::to_string(castEvent->controllerID) + ").");

                // player controller
                for (int i = 0; i < MAX_CONTROLLERS; i++)
                {
                    if (_playerAssignedControllerIDs[i] == -1)
                    {
                        _playerAssignedControllerIDs[i] = castEvent->controllerID;

                        Services::get().getLogger()->info("Input", "Controller (ID: " + std::to_string(castEvent->controllerID) + ") assigned to player #" + std::to_string(i) + ".");

                        break;
                    }
                }

                break;
            }

            case EventType::CONTROLLER_REMOVED:
            {
                EventControllerRemoved* castEvent = dynamic_cast<EventControllerRemoved*>(event);
                delete _controllers.at(castEvent->controllerID);
                _controllers.erase(static_cast<int>(castEvent->controllerID));

                Services::get().getLogger()->info("Input", "Controller disconnected (ID: " + std::to_string(castEvent->controllerID) + ").");

                for (int i = 0; i < MAX_CONTROLLERS; i++)
                {
                    if (_playerAssignedControllerIDs[i] == castEvent->controllerID)
                    {
                        _playerAssignedControllerIDs[i] = -1;

                        Services::get().getLogger()->info("Input", "Controller (ID: " + std::to_string(castEvent->controllerID) + ") unassigned from player #" + std::to_string(i) + ".");
                    }
                }

                break;
            }

            case EventType::CONTROLLER_JOYSTICK_MOVED:
            {
                EventControllerJoystickMoved* castEvent = static_cast<EventControllerJoystickMoved*>(event);

                // Services::get().getLogger()->debug("Input", "value: " + std::to_string(castEvent->value));

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

                default:
                    std::string errorMessage = "Cannot set value of axis #" + std::to_string(castEvent->axis) + " (does not exist).";
                    Services::get().getLogger()->error("Input", errorMessage);
                    Services::get().getLogger()->flush();
                    throw std::runtime_error(errorMessage);
                    
                }
                break;
            }

            case EventType::CONTROLLER_BUTTON_DOWN:
            {
                EventControllerButtonDown* castEvent = dynamic_cast<EventControllerButtonDown*>(event);
                _controllers[castEvent->controllerID]->setButtonState(castEvent->button, KeyState::PRESSED);

                switch (castEvent->button)
                {
                case ControllerButton::LEFT_DPAD:
                    _handleCursorMove(KeyCode::LEFT_ARROW);
                    break;

                case ControllerButton::RIGHT_DPAD:
                    _handleCursorMove(KeyCode::RIGHT_ARROW);
                    break;

                case ControllerButton::UP_DPAD:
                    _handleCursorMove(KeyCode::UP_ARROW);
                    break;

                case ControllerButton::DOWN_DPAD:
                    _handleCursorMove(KeyCode::DOWN_ARROW);
                    break;

                case ControllerButton::RIGHT_FACE:
                    if (_controllerCursorSelection != nullptr)
                    {
                        _controllerCursorSelection->click();
                        // is the nullptr check good? was a workaround for garter
                        if (_controllerCursorSelection && _controllerCursorSelection->getUnhoverOnClick())
                        {
                            _controllerCursorSelection = nullptr;
                        }
                    }
                    break;

                default:
                    break;
                }

                break;
            }

            case EventType::CONTROLLER_BUTTON_UP:
            {
                EventControllerButtonUp* castEvent = dynamic_cast<EventControllerButtonUp*>(event);
                _controllers[castEvent->controllerID]->setButtonState(castEvent->button, KeyState::RELEASED);
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

