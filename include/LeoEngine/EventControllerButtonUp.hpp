#ifndef EVENT_CONTROLLER_BUTTON_UP
#define EVENT_CONTROLLER_BUTTON_UP
 
#if defined(__linux__) || defined(__APPLE__)
    #include <SDL3/SDL.h>
#elif defined(_WIN32)
    #include <SDL.h>
#endif

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

