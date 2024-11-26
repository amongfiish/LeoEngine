#ifndef ENGINE_HPP
#define ENGINE_HPP

#if defined(__linux__) || defined(__APPLE__)
    #include <SDL2/SDL.h>
#elif defined(_WIN32)
    #include <SDL.h>
#endif

#include "Services.hpp"
#include "Graphics.hpp"
#include "Events.hpp"
#include "Input.hpp"
#include "Saver.hpp"
#include "Logger.hpp"
#include "Game.hpp"
#include "EngineSettings.hpp"

class Engine
{
public:
    Engine();
    Engine(EngineSettings& settings);
    ~Engine();

    void runGame(Game& game);

private:
    void quitCallback(Event *event);

    bool _running = true;
};

#endif

