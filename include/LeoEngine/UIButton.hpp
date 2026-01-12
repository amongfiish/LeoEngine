#ifndef UI_BUTTON_HPP
#define UI_BUTTON_HPP

#include <functional>

#include "LeoEngine/UIElement.hpp"
#include "LeoEngine/Rectangle.hpp"

namespace LeoEngine
{

    class Event;

    class UIButton : public UIElement
    {
    public:
        UIButton(std::function<void(void)> clickFunction, bool unhoverOnClick);
        virtual ~UIButton();

        void setSize(int width, int height);

    protected:
        static constexpr int _MOUSE_BUTTON = 1;

        void _mouseMovedCallback(Event *event);
        bool _clickCallback(Event *event);

        int _mouseMovedCallbackID;
        int _clickCallbackID;

        std::function<void(void)> _clickFunction;

        bool _mouseHovering;
        // should _mouseHovering be set to false in _clickCallback?
        bool _unhoverOnClick;
    };

}

#endif

