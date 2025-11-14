#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <map>
#include <unordered_map>
#include <vector>
#include <functional>
#include "LeoEngine/Event.hpp"
#include "LeoEngine/Pair.hpp"
using namespace std;

namespace LeoEngine
{

    typedef function<void(Event *)> VoidCallbackType;
    typedef function<bool(Event *)> BoolCallbackType;

    class Events
    {
    public:
        Events();
        ~Events() = default;

        // this has to be called every frame or the window won't function properly
        void sdlEventPoll();

        int addCallback(EventType type, VoidCallbackType callback);
        int addCallback(EventType type, BoolCallbackType callback);

        // ts seems really inefficient maybe we should change it sometime
        void removeCallback(int id);

        void broadcast(Event *event);

    private:
        int _nextID = 0;

        // not a very elegant solution but a solution nonetheless
        // to the issue of letting the UI get input events before the
        // input subsystem
        unordered_map<EventType, vector<Pair<int, BoolCallbackType>>> _priorityCallbacks;
        unordered_map<EventType, vector<Pair<int, VoidCallbackType>>> _callbacks;
    };

}

#endif

