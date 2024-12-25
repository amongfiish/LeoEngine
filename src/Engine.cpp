#if defined(__linux__) || defined(__APPLE__)
    #include <SDL2/SDL.h>
#elif defined(_WIN32)
    #include <SDL.h>
#endif

#include "Engine.hpp"
#include "Services.hpp"
#include "Graphics.hpp"
#include "Events.hpp"
#include "Input.hpp"
#include "Saver.hpp"
#include "Logger.hpp"

using namespace LeoEngine;

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

    Saver::setOrgAndAppName(settings.organizationName, settings.applicationName);
    Logger::setOrgAndAppName(settings.organizationName, settings.applicationName);
    
    Services::get().getLogger()->info("Core", "Testing");
}

Engine::~Engine()
{

}

void Engine::runGame(Game& game)
{
    const Colour BLACK(0, 0, 0, 255);

    int quitCallbackID = Services::get().getEvents()->addCallback(EventType::QUIT, bind(&Engine::quitCallback, this, placeholders::_1));

    const int MS_BETWEEN_UPDATES = 1000 / 60; // maybe stop hardcoding this?

    int previousFrameTicks = SDL_GetTicks();
    int currentFrameTicks = 0, totalUpdateLag = 0, ticksBetweenFrames = 0;
    
    while (_running)
    {
        // calculation to determine how far behind target UPS we are
        currentFrameTicks = SDL_GetTicks();
        ticksBetweenFrames = currentFrameTicks - previousFrameTicks;
        totalUpdateLag += ticksBetweenFrames;
        previousFrameTicks = currentFrameTicks;

        // SDL event loop
        Services::get().getEvents()->sdlEventPoll();

        // input update (run after event loop and before game update loop)
        Services::get().getInput()->update();

        // game update loop
        while (totalUpdateLag > MS_BETWEEN_UPDATES)
        {
            game.update();

            totalUpdateLag -= MS_BETWEEN_UPDATES;
        }

        // update camera
        Services::get().getGraphics()->updateCamera();

        // clear screen
        Services::get().getGraphics()->fill(BLACK);

        // draw
        game.draw();

        // show on the screen
        Services::get().getGraphics()->present();
    }

    Services::get().getEvents()->removeCallback(quitCallbackID);
}

void Engine::quitCallback(Event *event)
{
    _running = false;
}

