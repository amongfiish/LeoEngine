#include <stdexcept>
#include "LeoEngine/Font.hpp"

namespace LeoEngine
{

    Font::Font(string filepath)
    {
        TTF_Font *newFont = TTF_OpenFont(filepath.c_str(), 10);
        if (newFont == nullptr)
        {
            throw runtime_error("Couldn't load font.");
        }

        _font = newFont;
    }

    Font::~Font()
    {
        TTF_CloseFont(_font);
    }

    TTF_Font *Font::getSDLFontObject()
    {
        return _font;
    }

}
