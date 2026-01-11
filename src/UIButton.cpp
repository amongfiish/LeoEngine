#include "LeoEngine/UIButton.hpp"
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Events.hpp"
#include "LeoEngine/Event.hpp"
#include "LeoEngine/EventMouseButtonDown.hpp"
#include "LeoEngine/Input.hpp"
#include "LeoEngine/Collision.hpp"

namespace LeoEngine
{

    UIButton::UIButton(std::function<void(void)> clickFunction)
        : _mouseHovering(false),
          _clickFunction(clickFunction)
    {
        // explicit casting is necessary as Events::addCallback is overloaded
        _mouseMovedCallbackID = Services::get().getEvents()->addCallback(EventType::MOUSE_MOVED, static_cast<VoidCallbackType>(std::bind(&UIButton::_mouseMovedCallback, this, std::placeholders::_1)));
        _clickCallbackID = Services::get().getEvents()->addCallback(EventType::MOUSE_BUTTON_DOWN, static_cast<BoolCallbackType>(std::bind(&UIButton::_clickCallback, this, std::placeholders::_1)));
    }

    UIButton::~UIButton()
    {
        Services::get().getEvents()->removeCallback(_mouseMovedCallbackID);
        Services::get().getEvents()->removeCallback(_clickCallbackID);
    }

    void UIButton::setSize(int width, int height)
    {
        _bounds.width = width;
        _bounds.height = height;
    }

    void UIButton::_mouseMovedCallback(Event *event)
    {
        if (!_isActive)
        {
            return;
        }

        const LeoEngine::Pair<int, int>& mousePosition = Services::get().getInput()->getMousePosition();

        if (checkForOverlap(mousePosition, getGlobalBounds()))
        {
            _mouseHovering = true;
        }
        else
        {
            _mouseHovering = false;
        }
    }

    bool UIButton::_clickCallback(Event *event)
    {
        if (!_isActive)
        {
            return false;
        }

        EventMouseButtonDown *mouseButtonEvent = dynamic_cast<EventMouseButtonDown *>(event);

        if (mouseButtonEvent->mouseButton == _MOUSE_BUTTON && _mouseHovering)
        {
            _clickFunction();
            return true;
        }

        return false;
    }

}

