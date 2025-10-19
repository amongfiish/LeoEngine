#include "LeoEngine/Services.hpp"
#include "LeoEngine/Events.hpp"
#include "LeoEngine/Input.hpp"
#include "LeoEngine/Audio.hpp"
#include "LeoEngine/Graphics.hpp"
#include "LeoEngine/Logger.hpp"

namespace LeoEngine
{

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

    Actions *Services::getActions()
    {
        return _actions;
    }

    Services::Services()
            : _logger(new Logger),
            _events(new Events),
            _graphics(new Graphics),
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

}
