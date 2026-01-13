#ifndef EVENT_CONTROLLER_ADDED_HPP
#define EVENT_CONTROLLER_ADDED_HPP

#include <SDL3/SDL.h>

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

