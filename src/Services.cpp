#include "Services.hpp"
#include "Events.hpp"
#include "Input.hpp"
#include "Audio.hpp"
#include "Graphics.hpp"
#include "Logger.hpp"
#include "Saver.hpp"

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

Saver *Services::getSaver()
{
    return _saver;
}

Services::Services()
        : _logger(new Logger),
          _events(new Events),
          _graphics(new Graphics),
          _audio(new Audio),
          _input(new Input(_events)),
          _saver(new Saver("savedata"))
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

