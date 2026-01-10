#ifndef UI_BUTTON_TEXT_HPP
#define UI_BUTTON_TEXT_HPP

#include <functional>

#include "LeoEngine/UIButton.hpp"
#include "LeoEngine/UIText.hpp"
#include "LeoEngine/Colour.hpp"

namespace LeoEngine
{

    class UIButtonText : public UIButton
    {
    public:
        UIButtonText(std::function<void(void)> clickFunction);
        virtual ~UIButtonText() {};

        UIText& getText();

        void setColours(Colour backgroundColour, Colour backgroundColourHover, Colour outlineColour, Colour outlineColourHover);

    private:
        virtual void _draw() override;

        Colour _backgroundColour;
        Colour _backgroundColourHover;
        Colour _outlineColour;
        Colour _outlineColourHover;
        int _outlineThickness;

        UIText * const _text;
    };

}

#endif

