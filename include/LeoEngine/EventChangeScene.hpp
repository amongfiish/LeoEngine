#ifndef EVENT_CHANGE_SCENE_HPP
#define EVENT_CHANGE_SCENE_HPP

#include "LeoEngine/Event.hpp"

namespace LeoEngine
{

    class EventChangeScene : public Event
    {
    public:
        EventChangeScene(const int sceneID, const bool fade)
            : Event(EventType::CHANGE_SCENE),
            sceneID(sceneID),
            fade(fade)
        {

        }

        virtual ~EventChangeScene()
        {

        }

        const int sceneID;
        const bool fade;
    };

}

#endif
