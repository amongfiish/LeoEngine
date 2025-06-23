#ifndef GUI_TEXT_BOX_HPP
#define GUI_TEXT_BOX_HPP

#include <string>
#include <memory>
#include "LeoEngine/GUIObject.hpp"
#include "LeoEngine/TextDrawData.hpp"
#include "LeoEngine/Pair.hpp"

namespace LeoEngine
{

    class Texture;

    class GUITextBox : public GUIObject
    {
    public:
        GUITextBox(TextDrawData textDrawData);
        virtual ~GUITextBox();

        using GUIObject::update;
        virtual void update(Pair<int, int>& offset);

        using GUIObject::draw;
        virtual void draw(Pair<int, int>& offset);

        void setText(std::string text);

    protected:
        std::string _currentText;

        TextDrawData _textDrawData;
        std::shared_ptr<Texture> _renderedText;
    };

}

#endif

