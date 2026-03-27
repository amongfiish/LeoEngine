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

        void click();

        void setSize(int width, int height);

        void setLeftButton(UIButton* button);
        void setRightButton(UIButton* button);
        void setUpButton(UIButton* button);
        void setDownButton(UIButton* button);

        UIButton* getLeftButton();
        UIButton* getRightButton();
        UIButton* getUpButton();
        UIButton* getDownButton();

        bool getUnhoverOnClick() const;

    protected:
        static constexpr int _MOUSE_BUTTON = 1;

        void _setMouseHovering(bool hovering);

        void _mouseMovedCallback(Event *event);
        bool _clickCallback(Event *event);

        int _mouseMovedCallbackID;
        int _clickCallbackID;

        std::function<void(void)> _clickFunction;

        UIButton* _leftButton;
        UIButton* _rightButton;
        UIButton* _upButton;
        UIButton* _downButton;

        bool _cursorHovering;
        bool _unhoverOnClick;
    };

}

#endif

