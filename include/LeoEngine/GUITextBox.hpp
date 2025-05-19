#ifndef GUI_TEXT_BOX_HPP
#define GUI_TEXT_BOX_HPP

#include <string>
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

        virtual void update(Pair<int, int>& offset);
        void update();
        virtual void draw(Pair<int, int>& offset);
        void draw();

        void setText(std::string text);

    protected:
        std::string _currentText;

        TextDrawData _textDrawData;
        Texture *_renderedText;
    };

}

#endif

