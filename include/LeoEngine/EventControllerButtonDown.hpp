#ifndef EVENT_CONTROLLER_BUTTON_DOWN
#define EVENT_CONTROLLER_BUTTON_DOWN

#include <SDL3/SDL.h>

#include "LeoEngine/Event.hpp"
#include "LeoEngine/ControllerButton.hpp"

namespace LeoEngine
{

    class EventControllerButtonDown : public Event
    {
    public:
        EventControllerButtonDown(const SDL_JoystickID controllerID, const ControllerButton button)
            : Event(EventType::CONTROLLER_BUTTON_DOWN),
            controllerID(controllerID),
            button(button)
        {
        }

        virtual ~EventControllerButtonDown() final
        {
        }

        const SDL_JoystickID controllerID;
        const ControllerButton button;
    };

}

#endif

