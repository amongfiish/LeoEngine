#ifndef INPUT_HPP
#define INPUT_HPP

#if defined(__linux__) || defined(__APPLE__)
    #include <SDL2/SDL.h>
#elif defined(_WIN32)
    #include <SDL.h>
#endif

#include <vector>
#include <unordered_map>
#include "LeoEngine/KeyCode.hpp"
#include "LeoEngine/KeyState.hpp"
#include "LeoEngine/Pair.hpp"
#include "LeoEngine/Events.hpp"
#include "LeoEngine/Controller.hpp"

namespace LeoEngine
{

    class Input
    {
    public:
        Input(Events *events);
        ~Input();

        void update();

        // if input state is requested RELEASED will always be returned when locked
        void lockInput();
        void unlockInput();

        KeyState getKeyState(KeyCode keyCode) const;

        const Pair<int, int> &getMousePosition() const;
        KeyState getMouseButtonState(int buttonID) const;
        const Pair<int, int> &getMouseWheelMotion() const;

        KeyState getControllerButtonState(SDL_JoystickID controllerID, int buttonID) const;
        int getControllerJoystickState(SDL_JoystickID controllerID, int axis) const;

    private:
        void keyCallback(Event *event);
        void mouseCallback(Event *event);
        void controllerCallback(Event *event);

        bool _locked;

        Events *_events;

        std::unordered_map<KeyCode, KeyState> _keyStates;

        Pair<int, int> _mousePosition;
        std::vector<KeyState> _mouseButtons;
        Pair<int, int> _mouseWheelMotion;

        std::unordered_map<SDL_JoystickID, Controller> _controllers;
    };

}

#endif

