#if defined(__linux__) || defined(__APPLE__)
    #include <SDL3/SDL.h>
#elif defined(_WIN32)
    #include <SDL.h>
#endif

#include "LeoEngine/Engine.hpp"
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Graphics.hpp"
#include "LeoEngine/Events.hpp"
#include "LeoEngine/Input.hpp"
#include "LeoEngine/Logger.hpp"

#define DEFAULT_FRAMERATE 60

namespace LeoEngine
{

    Engine::Engine()
        : _running(false),
          _framerate(DEFAULT_FRAMERATE)
    {
        Services::get().getLogger()->info("Core", "Engine instance started.");
    }

    Engine::~Engine()
    {

    }

    void Engine::setFramerate(int framerate)
    {
        // this should be changed at some point to allow dynamic framerates
        if (_running)
        {
            std::string errorMessage = "Changing the framerate after the game has started. This will do nothing. How did you even get here?";
            Services::get().getLogger()->warn("Engine", errorMessage);

            return;
        }

        _framerate = framerate;
    }

    void Engine::runGame(Game& game)
    {
        const Colour BLACK(0, 0, 0, 255);

        int quitCallbackID = Services::get().getEvents()->addCallback(EventType::QUIT, bind(&Engine::quitCallback, this, placeholders::_1));

        const double NS_BETWEEN_FRAMES = 1000000000.0 / _framerate;

        double previousUpdateTicks = SDL_GetTicksNS();
        double previousDrawTicks = previousUpdateTicks;
        double currentTicks = 0;

        Services::get().getLogger()->info("Engine", "Entering main loop.");

        _running = true;
        while (_running)
        {
            currentTicks = SDL_GetTicksNS();

            double deltaTime = (currentTicks - previousUpdateTicks) / 1000000000.0;
            // LeoEngine::Services::get().getLogger()->debug("Engine", "deltaTime: " + std::to_string(deltaTime));
            
            // input update (run BEFORE event polling and game update)
            Services::get().getInput()->update();
            // SDL event loop
            Services::get().getEvents()->sdlEventPoll();
            game.update(deltaTime);

            previousUpdateTicks = currentTicks;

            if (currentTicks - previousDrawTicks >= NS_BETWEEN_FRAMES)
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
        }

        Services::get().getLogger()->info("Engine", "Exited main loop.");
        
        Services::get().getEvents()->removeCallback(quitCallbackID);
    }

    void Engine::quitCallback(Event *event)
    {
        _running = false;
    }

}
