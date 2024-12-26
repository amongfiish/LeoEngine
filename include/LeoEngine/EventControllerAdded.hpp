#ifndef EVENT_CONTROLLER_ADDED_HPP
#define EVENT_CONTROLLER_ADDED_HPP

#if defined(__linux__) || defined(__APPLE__)
    #include <SDL2/SDL.h>
#elif defined(_WIN32)
    #include <SDL.h>
#endif

#include "LeoEngine/Event.hpp"

namespace LeoEngine
{

    class EventControllerAdded : public Event
    {
    public:
        EventControllerAdded(const int controllerID)
            : Event(EventType::CONTROLLER_ADDED),
            controllerID(controllerID)
        {
        }

        virtual ~EventControllerAdded() final
        {
        }

        const int controllerID;
    };

}

#endif

