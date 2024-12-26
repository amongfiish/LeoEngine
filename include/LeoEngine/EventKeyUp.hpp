#ifndef EVENT_KEY_UP_HPP
#define EVENT_KEY_UP_HPP

#include "LeoEngine/Event.hpp"

namespace LeoEngine
{

    class EventKeyUp : public Event
    {
    public:
        EventKeyUp(const KeyCode keyCode)
            : Event(EventType::KEY_UP),
            keyCode(keyCode)
        {
        }

        virtual ~EventKeyUp() final
        {
        }

        const KeyCode keyCode;
    };

}

#endif

