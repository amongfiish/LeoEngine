#include <stdexcept>
#include <SDL3_image/SDL_image.h>
#include "LeoEngine/Window.hpp"
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Logger.hpp"
#include "LeoEngine/Events.hpp"
#include "LeoEngine/File.hpp"
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

    void Window::setGrabCursor(bool grabCursor)
    {
        SDL_SetWindowMouseGrab(_window, grabCursor);
    }

    void Window::setTitle(std::string title)
    {
        SDL_SetWindowTitle(_window, title.c_str());
    }

    void Window::setIcon(std::string filename)
    {
        std::string filePath = LeoEngine::File::getApplicationDataDirectory() + LeoEngine::File::getPathSeparator() + filename;

        SDL_Surface* iconSurface = IMG_Load(filePath.c_str());
        if (iconSurface == nullptr)
        {
            std::string errorMessage = "Could not load icon from file '" + filePath + "'. SDL Error: '" + SDL_GetError() + "'";
            LeoEngine::Services::get().getLogger()->error("Window", errorMessage);
            throw std::runtime_error(errorMessage);
        }
        
        SDL_SetWindowIcon(_window, iconSurface);
        SDL_DestroySurface(iconSurface);
    }

    void Window::windowResizeCallback(Event *event)
    {
        EventWindowResize *castEvent = dynamic_cast<EventWindowResize *>(event);

        _dimensions.first = castEvent->w;
        _dimensions.second = castEvent->h;
    }

}
