#ifndef SERVICES_HPP
#define SERVICES_HPP

namespace LeoEngine
{

    class Events;
    class Input;
    class Audio;
    class Graphics;
    class Logger;
    class Saver;
    class Actions;

    class Services
    {
    public:
        static Services &get();

        Events *getEvents();
        Input *getInput();
        Audio *getAudio();
        Graphics *getGraphics();
        Logger *getLogger();
        Saver *getSaver();
        Actions *getActions();

    private:
        Services();
        ~Services();

        static Services *_instance;

        Logger *_logger = nullptr;
        Events *_events = nullptr;
        Graphics *_graphics = nullptr;
        Audio *_audio = nullptr;
        Input *_input = nullptr;
        Saver *_saver = nullptr;
        Actions *_actions = nullptr;
    };

}

#endif
