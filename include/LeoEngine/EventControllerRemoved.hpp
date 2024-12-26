#ifndef EVENT_CONTROLLER_REMOVED_HPP
#define EVENT_CONTROLLER_REMOVED_HPP

#include "LeoEngine/Event.hpp"

namespace LeoEngine
{

    class EventControllerRemoved : public Event
    {
    public:
        EventControllerRemoved(const int controllerID)
            : Event(EventType::CONTROLLER_REMOVED),
            controllerID(controllerID)
        {
        }

        virtual ~EventControllerRemoved() final
        {
        }

        const int controllerID;
    };

}

#endif

