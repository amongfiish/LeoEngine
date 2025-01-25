#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#if defined(__linux__) || defined(__APPLE__)
    #include <SDL2/SDL.h>
#elif defined(_WIN32)
    #include <SDL.h>
#endif

#include <vector>
#include "LeoEngine/KeyState.hpp"

namespace LeoEngine
{

    class Controller
    {
    public:
        Controller(SDL_Joystick *sdlJoystick);
        ~Controller();

        void update();

        void setButtonState(int buttonID, KeyState buttonState);
        void setAxisState(int axisID, int axisState);

        KeyState getButtonState(int buttonID) const;
        int getAxisState(int axisID) const;

    private:
        SDL_Joystick *_sdlJoystick;

        std::vector<KeyState> _buttons;
        std::vector<int> _axes;
    };

}

#endif

