#ifndef EVENT_HPP
#define EVENT_HPP

namespace LeoEngine
{

    enum class EventType
    {
        QUIT,
        KEY_DOWN,
        KEY_UP,
        MOUSE_BUTTON_DOWN,
        MOUSE_BUTTON_UP,
        MOUSE_MOVED,
        MOUSE_WHEEL_MOVED,
        CONTROLLER_ADDED,
        CONTROLLER_REMOVED,
        CONTROLLER_JOYSTICK_MOVED,
        CONTROLLER_BUTTON_DOWN,
        CONTROLLER_BUTTON_UP,
        WINDOW_RESIZE,
        CHANGE_SCENE,
        CUSTOM
    };

    class Event
    {
    public:
        Event(EventType type)
            : type(type)
        {
        }

        virtual ~Event()
        {
        }

        const EventType type;
    };

}

#endif

