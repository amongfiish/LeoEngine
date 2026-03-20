#ifndef INPUT_HPP
#define INPUT_HPP

#include <SDL3/SDL.h>

#include <vector>
#include <map>
#include <string>
#include "LeoEngine/KeyCode.hpp"
#include "LeoEngine/KeyState.hpp"
#include "LeoEngine/Pair.hpp"
#include "LeoEngine/Events.hpp"
#include "LeoEngine/ControllerButton.hpp"

namespace LeoEngine
{

    class Controller;

    class Input
    {
    public:
        Input(Events *events);
        ~Input();

        void update();

        // RELEASED will always be returned by getKeyState() when _locked==true
        void lockInput();
        void unlockInput();

        KeyState getKeyState(KeyCode keyCode) const;
        std::string getKeyName(KeyCode keyCode) const;

        Pair<int, int> getMousePosition() const;
        KeyState getMouseButtonState(int buttonID) const;
        Pair<int, int> getMouseWheelMotion() const;

        std::vector<int> getConnectedControllers() const;

        KeyState getControllerButtonState(int controllerID, ControllerButton button) const;
        Pair<double, double> getControllerLeftJoystickAxes(int controllerID) const;
        Pair<double, double> getControllerRightJoystickAxes(int controllerID) const;
        double getControllerLeftTriggerAxis(int controllerID) const;
        double getControllerRightTriggerAxis(int controllerID) const;

    private:
        void keyCallback(Event *event);
        void controllerCallback(Event *event);
        void mouseCallback(Event *event);

        bool _locked;

        Events *_events;

        std::map<KeyCode, KeyState> _keyStates;

        std::map<int, Controller*> _controllers;

        Pair<int, int> _mousePosition;
        std::vector<KeyState> _mouseButtons;
        Pair<int, int> _mouseWheelMotion;
    };

}

#endif

