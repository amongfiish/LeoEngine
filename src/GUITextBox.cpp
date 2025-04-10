#include <memory>
#include <stdexcept>
#include "LeoEngine/GUITextBox.hpp"
#include "LeoEngine/Rectangle.hpp"
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Graphics.hpp"
#include "LeoEngine/Logger.hpp"

namespace LeoEngine
{

    GUITextBox::GUITextBox(TextDrawData textDrawData)
        : _renderedText(nullptr),
          _textDrawData(textDrawData)
    {
        
    }

    GUITextBox::~GUITextBox()
    {
        // might cause problems but we'll see...
        delete _renderedText;
    }

    void GUITextBox::update()
    {

    }

    void GUITextBox::draw()
    {
        if (_renderedText != nullptr)
        {
            std::shared_ptr<Rectangle> destRect = std::make_shared<Rectangle>(getDrawPosition(), _objectDimensions);
            TextureDrawData textDrawData(nullptr, destRect, 0, nullptr, FlipType::NONE);
            Services::get().getGraphics()->drawTextureCameraless(_renderedText, textDrawData);
        }
    }

    void GUITextBox::setText(std::string text)
    {
        if (_currentText == text)
        {
            return;
        }

        if (_renderedText != nullptr)
        {
            delete _renderedText;
            _renderedText = nullptr;
        }

        _renderedText = Services::get().getGraphics()->renderText(text, _textDrawData);
        if (_renderedText == nullptr)
        {
            Services::get().getLogger()->error("GUITextBox", "Failed to render text.");

            Services::get().getLogger()->flush();
            throw std::runtime_error("Failed to render text.");
        }

        _currentText = text;

        Pair<int, int> objectDimensions = _renderedText->getDimensions();
        _objectDimensions.first = objectDimensions.first;
        _objectDimensions.second = objectDimensions.second;
    }

}

