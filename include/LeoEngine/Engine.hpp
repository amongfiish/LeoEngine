#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "LeoEngine/EngineSettings.hpp"
#include "LeoEngine/Game.hpp"

namespace LeoEngine
{

    class Event;

    class Engine
    {
    public:
        Engine(EngineSettings &settings);
        ~Engine();

        void runGame(Game &game);

    private:
        void quitCallback(Event *event);

        bool _running = true;
    };

}

#endif

