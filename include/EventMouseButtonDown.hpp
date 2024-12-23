#ifndef EVENT_MOUSE_BUTTON_DOWN_HPP
#define EVENT_MOUSE_BUTTON_DOWN_HPP

#include "Event.hpp"

class EventMouseButtonDown : public Event
{
public:
    EventMouseButtonDown(const int mouseButton)
        : Event(EventType::MOUSE_BUTTON_DOWN),
          mouseButton(mouseButton)
    {}

    virtual ~EventMouseButtonDown() final {}

    const int mouseButton;
};

#endif

