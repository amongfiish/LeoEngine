#ifndef EVENT_CUSTOM_HPP
#define EVENT_CUSTOM_HPP

#include <string>
#include "LeoEngine/Event.hpp"

namespace LeoEngine
{

    class EventCustom : public Event
    {
    public:
        EventCustom(const string eventName)
            : Event(EventType::CUSTOM),
            eventName(eventName)
        {}

        virtual ~EventCustom()
        {}

        const string eventName;
    };

}

#endif

