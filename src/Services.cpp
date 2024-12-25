#include "Services.hpp"
#include "Events.hpp"
#include "Input.hpp"
#include "Audio.hpp"
#include "Graphics.hpp"
#include "Logger.hpp"
#include "Saver.hpp"

using namespace LeoEngine;

Services *Services::_instance = nullptr;

Services &Services::get()
{
    if (_instance == nullptr) 
    {
        _instance = new Services;
    }

    return *_instance;
}

LeoEngine::Events *Services::getEvents()
{
    return _events;
}

LeoEngine::Input *Services::getInput()
{
    return _input;
}

LeoEngine::Audio *Services::getAudio()
{
    return _audio;
}

LeoEngine::Graphics *Services::getGraphics()
{
    return _graphics;
}

LeoEngine::Logger *Services::getLogger()
{
    return _logger;
}

LeoEngine::Saver *Services::getSaver()
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

