#ifndef EVENT_CONTROLLER_REMOVED_HPP
#define EVENT_CONTROLLER_REMOVED_HPP

#include "Event.hpp"

class EventControllerRemoved : public Event
{
public:
    EventControllerRemoved(const int controllerID)
        : Event(EventType::CONTROLLER_REMOVED),
          controllerID(controllerID)
    {}

    virtual ~EventControllerRemoved() final {}

    const int controllerID;
};

#endif

