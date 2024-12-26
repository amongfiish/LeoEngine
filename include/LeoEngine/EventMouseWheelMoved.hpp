#ifndef EVENT_MOUSE_WHEEL_MOVED_HPP
#define EVENT_MOUSE_WHEEL_MOVED_HPP

#include "LeoEngine/Event.hpp"

namespace LeoEngine
{

    class EventMouseWheelMoved : public Event
    {
    public:
        EventMouseWheelMoved(const int x, const int y)
            : Event(EventType::MOUSE_WHEEL_MOVED),
            x(x), y(y)
        {
        }

        virtual ~EventMouseWheelMoved() final
        {
        }

        const int x, y;
    };

}

#endif

