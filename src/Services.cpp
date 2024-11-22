#include "Services.hpp"
#include "Events.hpp"
#include "Input.hpp"
#include "Audio.hpp"
#include "Graphics.hpp"
#include "Logger.hpp"
#include "GameSettings.hpp"

Services *Services::_instance = nullptr;

Services &Services::get()
{
    if (_instance == nullptr) 
    {
        _instance = new Services;
    }

    return *_instance;
}

Events *Services::getEvents()
{
    return _events;
}

Input *Services::getInput()
{
    return _input;
}

Audio *Services::getAudio()
{
    return _audio;
}

Graphics *Services::getGraphics()
{
    return _graphics;
}

Logger *Services::getLogger()
{
    return _logger;
}

Services::Services()
        : _logger(new Logger),
          _events(new Events),
          _graphics(new Graphics(GameSettings::DEFAULT_WINDOW_TITLE, GameSettings::DEFAULT_WINDOW_WIDTH, GameSettings::DEFAULT_WINDOW_HEIGHT)),
          _audio(new Audio),
          _input(new Input(_events))
{

}

Services::~Services()
{
    delete _events;
    delete _input;
    delete _audio;
    delete _graphics;
    delete _logger;

    delete _instance;
}

