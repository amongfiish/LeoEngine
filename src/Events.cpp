#if defined(__linux__) || defined(__APPLE__)
    #include <SDL2/SDL.h>
#elif defined(_WIN32)
    #include <SDL.h>
#endif

#include <stdexcept>
#include "LeoEngine/Events.hpp"
#include "LeoEngine/EventQuit.hpp"
#include "LeoEngine/EventKeyDown.hpp"
#include "LeoEngine/EventKeyUp.hpp"
#include "LeoEngine/EventMouseButtonDown.hpp"
#include "LeoEngine/EventMouseButtonUp.hpp"
#include "LeoEngine/EventMouseMoved.hpp"
#include "LeoEngine/EventMouseWheelMoved.hpp"
#include "LeoEngine/EventControllerAdded.hpp"
#include "LeoEngine/EventControllerRemoved.hpp"
#include "LeoEngine/EventControllerJoystickMoved.hpp"
#include "LeoEngine/EventControllerButtonDown.hpp"
#include "LeoEngine/EventControllerButtonUp.hpp"
#include "LeoEngine/EventWindowResize.hpp"
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Logger.hpp"

namespace LeoEngine
{

    Events::Events()
    {
        if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
        {
            throw std::runtime_error("Couldn't initialize SDL events subsystem.");
        }
    }

    void Events::sdlEventPoll()
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            Event *newEvent = nullptr;

            switch (e.type)
            {
            case SDL_QUIT:
                newEvent = static_cast<Event *>(new EventQuit);
                break;

            case SDL_KEYDOWN:
                newEvent = static_cast<Event *>(new EventKeyDown(static_cast<const KeyCode>(e.key.keysym.sym)));
                break;

            case SDL_KEYUP:
                newEvent = static_cast<Event *>(new EventKeyUp(static_cast<const KeyCode>(e.key.keysym.sym)));
                break;

            case SDL_MOUSEBUTTONDOWN:
                newEvent = static_cast<Event *>(new EventMouseButtonDown(static_cast<int>(e.button.button)));
                break;

            case SDL_MOUSEBUTTONUP:
                newEvent = static_cast<Event *>(new EventMouseButtonUp(static_cast<int>(e.button.button)));
                break;

            case SDL_MOUSEMOTION:
                newEvent = static_cast<Event *>(new EventMouseMoved(e.motion.x, e.motion.y));
                break;

            case SDL_MOUSEWHEEL:
                newEvent = static_cast<Event *>(new EventMouseWheelMoved(e.wheel.x, e.wheel.y));
                break;

            case SDL_JOYDEVICEADDED:
                newEvent = static_cast<Event *>(new EventControllerAdded(e.jdevice.which));
                break;

            case SDL_JOYDEVICEREMOVED:
                newEvent = static_cast<Event *>(new EventControllerRemoved(e.jdevice.which));
                break;

            case SDL_JOYAXISMOTION:
                newEvent = static_cast<Event *>(new EventControllerJoystickMoved(e.jaxis.which, e.jaxis.axis, e.jaxis.value));
                break;

            case SDL_JOYBUTTONDOWN:
                newEvent = static_cast<Event *>(new EventControllerButtonDown(e.jbutton.which, e.jbutton.button));
                break;

            case SDL_JOYBUTTONUP:
                newEvent = static_cast<Event *>(new EventControllerButtonUp(e.jbutton.which, e.jbutton.button));
                break;

            case SDL_WINDOWEVENT:
                if (e.window.event == SDL_WINDOWEVENT_RESIZED)
                {
                    newEvent = static_cast<Event *>(new EventWindowResize(e.window.data1, e.window.data2));
                }

                break;
            }

            if (newEvent != nullptr)
            {
                broadcast(newEvent);

                delete newEvent;
                newEvent = nullptr;
            }
        }
    }

    int Events::addCallback(EventType type, CallbackType callback)
    {
        if (_callbacks.find(type) == _callbacks.end())
        {
            _callbacks.insert(make_pair(type, vector<Pair<int, CallbackType>>()));
        }

        _callbacks.at(type).push_back(Pair<int, CallbackType>(_nextID, callback));

        return _nextID++;
    }

    void Events::removeCallback(int id)
    {
        for (auto eventVectorPair : _callbacks)
        {
            auto pairCallbackVector = eventVectorPair.second;
            for (int i = 0; i < pairCallbackVector.size(); i++)
            {
                if (pairCallbackVector.at(i).first == id)
                {
                    pairCallbackVector.erase(pairCallbackVector.begin() + i);
                }
            }
        }
    }

    void Events::broadcast(Event *event)
    {
        if (_callbacks.find(event->type) != _callbacks.end())
        {
            for (auto callback : _callbacks.at(event->type))
            {
                callback.second(event);
            }
        }
    }

}

