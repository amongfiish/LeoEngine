#ifndef CONTROLLER_BUTTON_HPP
#define CONTROLLER_BUTTON_HPP

#include <SDL3/SDL.h>

namespace LeoEngine
{

    const int NUMBER_OF_CONTROLLER_BUTTONS = 26;

    enum class ControllerButton
    {
        BOTTOM_FACE,
        RIGHT_FACE,
        LEFT_FACE,
        TOP_FACE,
        BACK,
        GUIDE,
        START,
        LEFT_STICK,
        RIGHT_STICK,
        LEFT_SHOULDER,
        RIGHT_SHOULDER,
        UP_DPAD,
        DOWN_DPAD,
        LEFT_DPAD,
        RIGHT_DPAD,
        MISC_1,
        RIGHT_PADDLE_1,
        LEFT_PADDLE_1,
        RIGHT_PADDLE_2,
        LEFT_PADDLE_2,
        TOUCHPAD,
        MISC_2,
        MISC_3,
        MISC_4,
        MISC_5,
        MISC_6
    };

}

#endif

