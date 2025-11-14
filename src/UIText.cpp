#include "LeoEngine/UIText.hpp"
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Graphics.hpp"
#include "LeoEngine/Logger.hpp"
#include "LeoEngine/Pair.hpp"
#include "LeoEngine/TextureDrawData.hpp"

#include <memory>
#include <stdexcept>

namespace LeoEngine
{

    UIText::UIText()
        : _textDrawData(std::string(), 0, Colour()),
          _renderedText(nullptr)
    {

    }

    UIText::~UIText()
    {

    }

    void UIText::setText(std::string text)
    {
        if (text != _text)
        {
            _text = text;
            renderText();
        }
    }

    void UIText::setFontFilename(std::string filename)
    {
        if (filename != _textDrawData.fontFilename)
        {
            _textDrawData.fontFilename = filename;
            renderText();
        }
    }

    void UIText::setTextSize(int size)
    {
        if (size != _textDrawData.pointSize)
        {
            _textDrawData.pointSize = size;
            renderText();
        }
    }

    void UIText::setTextColour(Colour colour)
    {
        if (colour != _textDrawData.colour)
        {
            _textDrawData.colour = colour;
            renderText();
        }
    }

    void UIText::renderText()
    {
        if (_textDrawData.fontFilename.empty())
        {
            std::string errorMessage = "Skipping renderText call as the font filename hasn't been initialized yet.";
            Services::get().getLogger()->warn("UIText", errorMessage);
            return;
        }

        if (_textDrawData.pointSize <= 0)
        {
            std::string errorMessage = "Skipping renderText call as the font size hasn't been initialized yet.";
            Services::get().getLogger()->warn("UIText", errorMessage);
            return;
        }

        _renderedText = Services::get().getGraphics()->renderText(_text, _textDrawData);
        
        Pair<int, int> textDimensions = _renderedText->getDimensions();
        _bounds.width = textDimensions.first;
        _bounds.height = textDimensions.second;
    }

    void UIText::drawInternal()
    {
        if (_renderedText == nullptr)
        {
            std::string errorMessage = "Attempting to draw text that hasn't been rendered yet. Either deactivate this UIText or initialize all fields before the first draw call.";
            Services::get().getLogger()->error("UIText", errorMessage);
            Services::get().getLogger()->flush();
            throw std::runtime_error(errorMessage);
        }

        TextureDrawData textureDrawData;
        textureDrawData.destinationRectangle = std::make_shared<Rectangle<int>>(getGlobalBounds());

        Services::get().getGraphics()->drawTextureCameraless(*_renderedText, textureDrawData);
    }

}

