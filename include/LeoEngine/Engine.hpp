#ifndef ENGINE_HPP
#define ENGINE_HPP

#define SDL_MAIN_HANDLED

#include "LeoEngine/Game.hpp"

namespace LeoEngine
{
    class Event;

    class Engine
    {
    public:
        Engine();
        ~Engine();

        void setFramerate(int framerate);
        void runGame(Game &game);

    private:
        void quitCallback(Event *event);

        bool _running;

        long long _nsBetweenFrames;
    };

}

#endif
