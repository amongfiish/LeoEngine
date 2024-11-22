#if defined(__linux__) || defined(__APPLE__)
    #include <SDL2/SDL.h>
#elif defined(_WIN32)
    #include <SDL.h>
#endif

#include "Services.hpp"
#include "Graphics.hpp"
#include "Events.hpp"
#include "Input.hpp"
#include "Game.hpp"
#include "GameSettings.hpp"
using namespace std;

// yucky global LOL
bool running = true;

void quitCallback(Event *event);

int main(int argc, char *argv[])
{
    // used to clear the screen
    const Colour BLACK(0, 0, 0, 255);

    // quit callback for when the window closes
    int quitCallbackID = Services::get().getEvents()->addCallback(EventType::QUIT, quitCallback);

    // setup graphics
    Services::get().getGraphics()->setRenderDimensions(GameSettings::DEFAULT_RENDER_WIDTH, GameSettings::DEFAULT_RENDER_HEIGHT);
    Services::get().getGraphics()->setRenderVSync(true);

    // initialize game class
    Game game;

    // uses GameSettings::TARGET_UPS to determine how long to wait between updates
    const int MS_BETWEEN_UPDATES = 1000 / GameSettings::TARGET_UPS;

    int previousFrameTicks = SDL_GetTicks();
    int currentFrameTicks, totalUpdateLag, ticksBetweenFrames;
    while (running)
    {
        // determine how far behind target UPS we are
        currentFrameTicks = SDL_GetTicks();
        ticksBetweenFrames = currentFrameTicks - previousFrameTicks;
        totalUpdateLag += ticksBetweenFrames;
        previousFrameTicks = currentFrameTicks;

        // SDL event loop
        Services::get().getEvents()->sdlEventPoll();
        // input update MUST BE RUN AFTER SDL EVENT LOOP TO BE ACCURATE
        // should also be called before the game update loop
        Services::get().getInput()->update();

        // update
        while (totalUpdateLag > MS_BETWEEN_UPDATES)
        {
            game.update();
            
            totalUpdateLag -= MS_BETWEEN_UPDATES;
        }

        // updates the cameras before drawing
        Services::get().getGraphics()->updateCamera();

        // draw
        Services::get().getGraphics()->fill(BLACK);

        game.draw();
        
        Services::get().getGraphics()->present();
    }

    Services::get().getEvents()->removeCallback(quitCallbackID);

    return 0;
}

// when the window is closed, tell the main loop to stop
void quitCallback(Event *event)
{
    running = false;
}

