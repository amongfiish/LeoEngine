#ifndef EVENT_QUIT_HPP
#define EVENT_QUIT_HPP

#include "Event.hpp"

class EventQuit : public Event
{
public:
    EventQuit()
        : Event(EventType::QUIT)
    {}

    virtual ~EventQuit() final {}
};

#endif

