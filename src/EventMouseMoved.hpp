#ifndef EVENT_MOUSE_MOVED_HPP
#define EVENT_MOUSE_MOVED_HPP

#include "Event.hpp"

class EventMouseMoved : public Event
{
public:
    EventMouseMoved(const int x, const int y)
        : Event(EventType::MOUSE_MOVED),
        x(x), y(y)
    {}

    virtual ~EventMouseMoved() final
    {}

    const int x, y;
};

#endif

