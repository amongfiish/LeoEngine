#ifndef INPUT_HPP
#define INPUT_HPP

#include <SDL3/SDL.h>

#include <vector>
#include <unordered_map>
#include <string>
#include "LeoEngine/KeyCode.hpp"
#include "LeoEngine/KeyState.hpp"
#include "LeoEngine/Pair.hpp"
#include "LeoEngine/Events.hpp"

namespace LeoEngine
{

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

        const Pair<int, int> &getMousePosition() const;
        KeyState getMouseButtonState(int buttonID) const;
        const Pair<int, int> &getMouseWheelMotion() const;

        // TODO: re-add controller stuff

    private:
        void keyCallback(Event *event);
        void mouseCallback(Event *event);

        bool _locked;

        Events *_events;

        std::unordered_map<KeyCode, KeyState> _keyStates;

        Pair<int, int> _mousePosition;
        std::vector<KeyState> _mouseButtons;
        Pair<int, int> _mouseWheelMotion;
    };

}

#endif

