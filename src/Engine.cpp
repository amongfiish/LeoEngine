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

namespace LeoEngine
{

    bool running = true;

    Engine::Engine(EngineSettings& settings)
    {
        Services::get().getGraphics()->setWindowDimensions(settings.defaultWindowWidth, settings.defaultWindowHeight);
        Services::get().getGraphics()->setRenderDimensions(settings.defaultRenderWidth, settings.defaultRenderHeight);

        Services::get().getGraphics()->setWindowFullscreen(settings.defaultFullscreen);
        Services::get().getGraphics()->setWindowBordered(settings.defaultBordered);
        Services::get().getGraphics()->setWindowResizable(settings.defaultResizable);

        Services::get().getGraphics()->setWindowTitle(settings.defaultWindowTitle);

        Services::get().getGraphics()->setRenderVSync(true);

        Services::get().getLogger()->setOrgAndAppName(settings.organizationName, settings.applicationName);

        _framerate = settings.framerate;
        
        Services::get().getLogger()->info("Core", "Engine instance initialized.");
    }

    Engine::~Engine()
    {

    }

    void Engine::runGame(Game& game)
    {
        const Colour BLACK(0, 0, 0, 255);

        int quitCallbackID = Services::get().getEvents()->addCallback(EventType::QUIT, bind(&Engine::quitCallback, this, placeholders::_1));

        const int MS_BETWEEN_FRAMES = 1000 / _framerate;

        int previousUpdateTicks = SDL_GetTicks();
        int previousDrawTicks = previousUpdateTicks;
        int currentTicks = 0;

        Services::get().getLogger()->info("Core", "Entering main loop.");
        
        while (_running)
        {
            currentTicks = SDL_GetTicks();

            double deltaTime = (currentTicks - previousUpdateTicks) / 1000.0;
            
            // input update (run BEFORE event polling and game update)
            Services::get().getInput()->update();
            // SDL event loop
            Services::get().getEvents()->sdlEventPoll();
            game.update(deltaTime);

            previousUpdateTicks = currentTicks;

            if (currentTicks - previousDrawTicks >= MS_BETWEEN_FRAMES)
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

        Services::get().getLogger()->info("Core", "Exited main loop.");
        
        Services::get().getEvents()->removeCallback(quitCallbackID);
    }

    void Engine::quitCallback(Event *event)
    {
        _running = false;
    }

}
