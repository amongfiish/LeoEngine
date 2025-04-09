#include "LeoEngine/GUITextBox.hpp"
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Graphics.hpp"

namespace LeoEngine
{

    GUITextBox::GUITextBox(TextDrawData textDrawData)
        : _renderedText(nullptr),
          _textDrawData(textDrawData)
    {
        
    }

    GUITextBox::~GUITextBox()
    {

    }

    void GUITextBox::update()
    {

    }

    void GUITextBox::draw()
    {
        
    }

    void GUITextBox::setText(std::string text)
    {
        if (_renderedText != nullptr)
        {
            delete _renderedText;
            _renderedText = nullptr;
        }

        _renderedText = Services::get().getGraphics()->renderText(text, _textDrawData);

        Pair<int, int> objectDimensions = _renderedText->getDimensions();
        _objectDimensions.first = objectDimensions.first;
        _objectDimensions.second = objectDimensions.second;
    }

}

