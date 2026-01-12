#include "LeoEngine/UIButtonText.hpp"
#include "LeoEngine/Rectangle.hpp"
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Graphics.hpp"

namespace LeoEngine
{

    UIButtonText::UIButtonText(std::function<void(void)> clickFunction, bool unhoverOnClick)
        : UIButton(clickFunction, unhoverOnClick),
          _text(createChild<UIText>()),
          _backgroundColour(0xFF, 0xFF, 0xFF, 0xFF),
          _backgroundColourHover(0xAA, 0xAA, 0xAA, 0xFF),
          _outlineColour(0x00, 0x00, 0x00, 0xFF),
          _outlineColourHover(0x00, 0x00, 0x00, 0xFF)
    {

    }

    UIText& UIButtonText::getText()
    {
        return *_text;
    }

    void UIButtonText::setColours(Colour backgroundColour, Colour backgroundColourHover, Colour outlineColour, Colour outlineColourHover)
    {
        _backgroundColour = backgroundColour;
        _backgroundColourHover = backgroundColourHover;
        _outlineColour = outlineColour;
        _outlineColourHover = outlineColourHover;
    }

    void UIButtonText::_draw()
    {
        Rectangle<int> globalBounds = getGlobalBounds();

        Colour *backgroundColour = &_backgroundColour;
        Colour *outlineColour = &_outlineColour;

        if (_mouseHovering)
        {
            backgroundColour = &_backgroundColourHover;
            outlineColour = &_outlineColourHover;
        }

        Services::get().getGraphics()->drawRectangleCameraless(*backgroundColour, true, globalBounds);
        Services::get().getGraphics()->drawRectangleCameraless(*outlineColour, false, globalBounds);

        _text->draw();
    }

}

