#ifndef EVENT_CUSTOM_HPP
#define EVENT_CUSTOM_HPP

#include <string>
#include "Event.hpp"

class EventCustom : public Event
{
public:
    EventCustom(const string eventName)
        : Event(EventType::CUSTOM),
          eventName(eventName)
    {}

    virtual ~EventCustom() final {}

    const string eventName;
};

#endif

