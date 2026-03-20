#ifndef EVENT_CONTROLLER_BUTTON_UP
#define EVENT_CONTROLLER_BUTTON_UP
 
#include <SDL3/SDL.h>

#include "LeoEngine/Event.hpp"
#include "LeoEngine/ControllerButton.hpp"

namespace LeoEngine
{

    class EventControllerButtonUp : public Event
    {
    public:
        EventControllerButtonUp(const SDL_JoystickID controllerID, const ControllerButton button)
            : Event(EventType::CONTROLLER_BUTTON_UP),
            controllerID(controllerID),
            button(button)
        {
        }

        virtual ~EventControllerButtonUp() final
        {
        }

        const SDL_JoystickID controllerID;
        const ControllerButton button;
    };

}

#endif

