#include <stdexcept>
#include "LeoEngine/Window.hpp"
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Events.hpp"
#include "LeoEngine/EventWindowResize.hpp"

#define DEFAULT_WINDOW_TITLE "LeoDefaultWindowTitle"
#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600

namespace LeoEngine
{

    Window::Window()
    {
        SDL_Window *newWindow = SDL_CreateWindow(DEFAULT_WINDOW_TITLE, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, 0);
        if (newWindow == nullptr)
        {
            throw std::runtime_error("Window could not be created.");
        }

        _dimensions.first = DEFAULT_WINDOW_WIDTH;
        _dimensions.second = DEFAULT_WINDOW_HEIGHT;

        _window = newWindow;
    }

    Window::~Window()
    {
        if (_window != nullptr)
        {
            SDL_DestroyWindow(_window);
        }
    }

    void Window::postInitialization()
    {
        Services::get().getEvents()->addCallback(EventType::WINDOW_RESIZE, std::bind(&Window::windowResizeCallback, this, placeholders::_1));
    }

    SDL_Window *Window::getSDLWindowObject() const
    {
        return _window;
    }

    void Window::setDimensions(const int width, const int height)
    {
        SDL_SetWindowSize(_window, width, height);

        _dimensions.first = width;
        _dimensions.second = height;
    }

    void Window::setDimensions(const Pair<int, int>& dimensions)
    {
        setDimensions(dimensions.first, dimensions.second);
    }

    Pair<int, int> Window::getDimensions() const
    {
        return _dimensions;
    }

    void Window::setFullscreen(bool isFullscreen)
    {
        SDL_SetWindowFullscreen(_window, isFullscreen ? SDL_WINDOW_FULLSCREEN : 0);
    }

    void Window::setBordered(bool isBordered)
    {
        SDL_SetWindowBordered(_window, isBordered);
    }

    void Window::setResizable(bool isResizable)
    {
        SDL_SetWindowResizable(_window, isResizable);
    }

    void Window::setTitle(std::string title)
    {
        SDL_SetWindowTitle(_window, title.c_str());
    }

    void Window::windowResizeCallback(Event *event)
    {
        EventWindowResize *castEvent = dynamic_cast<EventWindowResize *>(event);

        _dimensions.first = castEvent->w;
        _dimensions.second = castEvent->h;
    }

}
