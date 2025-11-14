#include "LeoEngine/UIFrame.hpp"
#include "LeoEngine/Pair.hpp"
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Graphics.hpp"

namespace LeoEngine
{

    UIFrame::UIFrame()
    {
        Pair<int, int> renderDimensions = Services::get().getGraphics()->getRenderDimensions();
        _bounds.width = renderDimensions.first;
        _bounds.height = renderDimensions.second;
    }

    UIFrame::~UIFrame()
    {

    }

    void UIFrame::setSize(const Pair<int, int>& size)
    {
        _bounds.x = size.first;
        _bounds.y = size.second;
    }

}

