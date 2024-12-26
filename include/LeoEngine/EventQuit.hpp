#ifndef EVENT_QUIT_HPP
#define EVENT_QUIT_HPP

#include "LeoEngine/Event.hpp"

namespace LeoEngine
{

    class EventQuit : public Event
    {
    public:
        EventQuit()
            : Event(EventType::QUIT)
        {
        }

        virtual ~EventQuit() final
        {
        }
    };

}

#endif

