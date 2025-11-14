#ifndef WINDOW_HPP
#define WINDOW_HPP

#if defined(__linux__) || defined(__APPLE__)
    #include <SDL3/SDL.h>
#elif defined(_WIN32)
    #include <SDL.h>
#endif
#include <string>
#include "LeoEngine/Pair.hpp"
#include "LeoEngine/Colour.hpp"
#include "LeoEngine/Event.hpp"

namespace LeoEngine
{

    // TODO Add High DPI support for mac and ios
    class Window
    {
    public:
        Window();
        ~Window();

        void postInitialization();

        SDL_Window *getSDLWindowObject() const;

        void setDimensions(int width, int height);
        void setDimensions(const Pair<int, int> &dimensions);
        Pair<int, int> getDimensions() const;

        void setFullscreen(bool isFullscreen);
        void setBordered(bool isBordered);
        void setResizable(bool isResizable);
        void setGrabCursor(bool grabCursor);

        void setTitle(std::string title);

    private:
        void windowResizeCallback(Event *event);

        SDL_Window *_window = nullptr;

        Pair<int, int> _dimensions;
    };

}

#endif

