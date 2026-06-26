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

        void setLockFramerate(bool lockFramerate);
        void setFramerate(int framerate);
        void setFixedUpdateRate(int fixedUpdateRate);
        void runGame(Game &game);

    private:
        void quitCallback(Event *event);

        bool _running;

        bool _lockFramerate;

        long long _nsBetweenFrames;
        long long _nsBetweenFixedUpdates;
    };

}

#endif
