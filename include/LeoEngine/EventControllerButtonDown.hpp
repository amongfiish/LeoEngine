#ifndef EVENT_CONTROLLER_BUTTON_DOWN
#define EVENT_CONTROLLER_BUTTON_DOWN

#include <SDL3/SDL.h>

#include "LeoEngine/Event.hpp"

namespace LeoEngine
{

    class EventControllerButtonDown : public Event
    {
    public:
        EventControllerButtonDown(const SDL_JoystickID controllerID, const int buttonID)
            : Event(EventType::CONTROLLER_BUTTON_DOWN),
            controllerID(controllerID),
            buttonID(buttonID)
        {
        }

        virtual ~EventControllerButtonDown() final
        {
        }

        const SDL_JoystickID controllerID;
        const int buttonID;
    };

}

#endif

