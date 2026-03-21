#include <SDL3/SDL.h>

#include "LeoEngine/Engine.hpp"
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Graphics.hpp"
#include "LeoEngine/Events.hpp"
#include "LeoEngine/Input.hpp"
#include "LeoEngine/Logger.hpp"

#define DEFAULT_FRAMERATE 60
#define DEFAULT_FIXED_UPDATE_RATE 60
#define NANO_PER_SECOND 1000000000.0

namespace LeoEngine
{

    Engine::Engine()
        : _running(false)
    {
        setFramerate(DEFAULT_FRAMERATE);
        setFixedUpdateRate(DEFAULT_FIXED_UPDATE_RATE);
    }

    Engine::~Engine()
    {

    }

    void Engine::setFramerate(int framerate)
    {
        _nsBetweenFrames = static_cast<long long>(NANO_PER_SECOND / framerate);
    }

    void Engine::setFixedUpdateRate(int fixedUpdateRate)
    {
        _nsBetweenFixedUpdates = static_cast<long long>(NANO_PER_SECOND / fixedUpdateRate);
    }

    void Engine::runGame(Game& game)
    {
        const Colour BLACK(0, 0, 0, 255);

        int quitCallbackID = Services::get().getEvents()->addCallback(EventType::QUIT, bind(&Engine::quitCallback, this, placeholders::_1));

        long long previousUpdateTicks = SDL_GetTicksNS();
        long long previousFixedUpdateTicks = previousUpdateTicks;
        long long previousDrawTicks = previousUpdateTicks;
        long long currentTicks = 0;

        Services::get().getLogger()->info("Engine", "Engine started.");

        _running = true;
        while (_running)
        {
            currentTicks = SDL_GetTicksNS();

            double deltaTime = (currentTicks - previousUpdateTicks) / NANO_PER_SECOND;
            // LeoEngine::Services::get().getLogger()->debug("Engine", "deltaTime: " + std::to_string(deltaTime));
            // LeoEngine::Services::get().getLogger()->debug("Engine", "UPS: " + std::to_string(1.0/deltaTime));
            
            // input update (run BEFORE event polling and game update)
            Services::get().getInput()->update();
            // SDL event loop
            Services::get().getEvents()->sdlEventPoll();
            game.update(deltaTime);

            previousUpdateTicks = currentTicks;

            if (currentTicks - previousDrawTicks >= _nsBetweenFrames)
            {
                // update camera
                Services::get().getGraphics()->updateCamera();

                // clear screen
                Services::get().getGraphics()->fill(BLACK);
                // draw
                game.draw();
                // show on the screen
                Services::get().getGraphics()->present();

                previousDrawTicks = currentTicks;
            }

            while (currentTicks - previousFixedUpdateTicks >= _nsBetweenFixedUpdates)
            {
                game.fixedUpdate(_nsBetweenFixedUpdates / NANO_PER_SECOND);
                previousFixedUpdateTicks += _nsBetweenFixedUpdates;
            }
        }

        Services::get().getLogger()->info("Engine", "Engine finished.");
        
        Services::get().getEvents()->removeCallback(quitCallbackID);
    }

    void Engine::quitCallback(Event *event)
    {
        _running = false;
    }

}
