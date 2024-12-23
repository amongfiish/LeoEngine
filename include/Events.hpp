#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <map>
#include <unordered_map>
#include <vector>
#include <functional>
#include "Event.hpp"
#include "Pair.hpp"
using namespace std;

typedef function<void(Event *)> CallbackType;

class Events
{
public:
    Events();
    ~Events() = default;

    // this has to be called every frame or the window won't function properly
    void sdlEventPoll();

    int addCallback(EventType type, CallbackType callback);
    void removeCallback(int id);

    void broadcast(Event *event);

private:
    int _nextID = 0;

    unordered_map<EventType, vector<Pair<int, CallbackType>>> _callbacks;
};

#endif

