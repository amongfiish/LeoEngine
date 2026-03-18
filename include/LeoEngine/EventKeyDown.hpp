#ifndef EVENT_KEY_DOWN_HPP
#define EVENT_KEY_DOWN_HPP

#include "LeoEngine/Event.hpp"
#include "LeoEngine/KeyCode.hpp"

namespace LeoEngine
{

    class EventKeyDown : public Event
    {
    public:
        EventKeyDown(const KeyCode keyCode)
            : Event(EventType::KEY_DOWN),
              keyCode(keyCode),
              isRepeat(false)
        {
        }

        virtual ~EventKeyDown() final
        {
        }

        const KeyCode keyCode;
        bool isRepeat;
    };

}

#endif

