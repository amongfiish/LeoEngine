#ifndef EVENT_CONTROLLER_BUTTON_DOWN
#define EVENT_CONTROLLER_BUTTON_DOWN

#if defined(__linux__) || defined(__APPLE__)
    #include <SDL2/SDL.h>
#elif defined(_WIN32)
    #include <SDL.h>
#endif

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

