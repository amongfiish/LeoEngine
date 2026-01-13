#ifndef EVENT_CONTROLLER_BUTTON_UP
#define EVENT_CONTROLLER_BUTTON_UP
 
#include <SDL3/SDL.h>

#include "LeoEngine/Event.hpp"

namespace LeoEngine
{

    class EventControllerButtonUp : public Event
    {
    public:
        EventControllerButtonUp(const SDL_JoystickID controllerID, const int buttonID)
            : Event(EventType::CONTROLLER_BUTTON_UP),
            controllerID(controllerID),
            buttonID(buttonID)
        {
        }

        virtual ~EventControllerButtonUp() final
        {
        }

        const SDL_JoystickID controllerID;
        const int buttonID;
    };

}

#endif

