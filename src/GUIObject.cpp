#include "LeoEngine/GUIObject.hpp"

namespace LeoEngine
{

    void GUIObject::setAnchor(GUIAnchor anchor)
    {
        _anchor = anchor;
    }

    void GUIObject::setAnchorPosition(int x, int y)
    {
        _anchorPosition.first = x;
        _anchorPosition.second = y;
    }

    void GUIObject::setAnchorPosition(Pair<int, int>& position)
    {
        _anchorPosition.first = position.first;
        _anchorPosition.second = position.second;
    }

}

