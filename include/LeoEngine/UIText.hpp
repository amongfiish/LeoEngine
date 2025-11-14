#ifndef UI_TEXT_HPP
#define UI_TEXT_HPP

#include <string>
#include <memory>

#include "LeoEngine/UIElement.hpp"
#include "LeoEngine/TextDrawData.hpp"
#include "LeoEngine/Texture.hpp"

namespace LeoEngine
{

    class UIText : public UIElement
    {
    public:
        UIText();
        virtual ~UIText();

        void setText(std::string text);
        void setFontFilename(std::string filename);
        void setTextSize(int size);
        void setTextColour(Colour colour);

    private:
        void renderText();

        virtual void drawInternal() override;

        std::string _text;
        TextDrawData _textDrawData;

        std::shared_ptr<Texture> _renderedText;
    };

}

#endif

