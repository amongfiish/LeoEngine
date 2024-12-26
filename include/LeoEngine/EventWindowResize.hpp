#ifndef EVENT_WINDOW_RESIZE_HPP
#define EVENT_WINDOW_RESIZE_HPP

#include "LeoEngine/Event.hpp"

namespace LeoEngine
{

    class EventWindowResize : public Event
    {
    public:
        EventWindowResize(int w, int h)
            : Event(EventType::WINDOW_RESIZE),
            w(w),
            h(h)
        {
        }

        virtual ~EventWindowResize() final
        {
        }

        int w, h;
    };

}

#endif

