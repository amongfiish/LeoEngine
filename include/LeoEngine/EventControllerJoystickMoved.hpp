#ifndef EVENT_CONTROLLER_JOYSTICK_MOVED_HPP
#define EVENT_CONTROLLER_JOYSTICK_MOVED_HPP

#include <SDL3/SDL.h>

#include "LeoEngine/Event.hpp"

namespace LeoEngine
{

    class EventControllerJoystickMoved : public Event
    {
    public:
        EventControllerJoystickMoved(const SDL_JoystickID controllerID, const int axis, const int value)
            : Event(EventType::CONTROLLER_JOYSTICK_MOVED),
            controllerID(controllerID),
            axis(axis), value(value)
        {
        }

        virtual ~EventControllerJoystickMoved() final
        {
        }

        const SDL_JoystickID controllerID;
        const int axis, value;
    };

}

#endif

