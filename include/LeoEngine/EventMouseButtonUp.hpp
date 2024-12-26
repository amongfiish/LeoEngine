#ifndef EVENT_MOUSE_BUTTON_UP_HPP
#define EVENT_MOUSE_BUTTON_UP_HPP

#include "LeoEngine/Event.hpp"

namespace LeoEngine
{

    class EventMouseButtonUp : public Event
    {
    public:
        EventMouseButtonUp(const int mouseButton)
            : Event(EventType::MOUSE_BUTTON_UP),
            mouseButton(mouseButton)
        {
        }

        virtual ~EventMouseButtonUp() final
        {
        }

        const int mouseButton;
    };

}

#endif

