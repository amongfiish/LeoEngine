#ifndef EVENT_KEY_DOWN_HPP
#define EVENT_KEY_DOWN_HPP

#include "Event.hpp"
#include "KeyCode.hpp"

class EventKeyDown : public Event
{
public:
    EventKeyDown(const KeyCode keyCode)
        : Event(EventType::KEY_DOWN),
          keyCode(keyCode)
    {}

    virtual ~EventKeyDown() final {}

    const KeyCode keyCode;
};

#endif

