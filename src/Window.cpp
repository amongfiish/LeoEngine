#include <stdexcept>
#include "LeoEngine/Window.hpp"
using namespace std;

namespace LeoEngine
{

    Window::Window(string title, int width, int height)
    {
        SDL_Window *newWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
        if (newWindow == nullptr)
        {
            throw runtime_error("Window could not be created.");
        }

        _dimensions.first = width;
        _dimensions.second = height;

        _window = newWindow;
    }

    Window::~Window()
    {
        if (_window != nullptr)
        {
            SDL_DestroyWindow(_window);
        }
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
        SDL_SetWindowBordered(_window, static_cast<SDL_bool>(isBordered));
    }

    void Window::setResizable(bool isResizable)
    {
        SDL_SetWindowResizable(_window, static_cast<SDL_bool>(isResizable));
    }

    void Window::setTitle(string title)
    {
        SDL_SetWindowTitle(_window, title.c_str());
    }

}
