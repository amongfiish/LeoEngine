#include "LeoEngine/GUIObject.hpp"

namespace LeoEngine
{

    GUIObject::GUIObject()
        : _anchor(GUIAnchor::TOP_LEFT),
          _anchorPosition(0, 0),
          _objectDimensions(0, 0)
    {}

    GUIObject::~GUIObject()
    {}

    void GUIObject::update()
    {
        Pair<int, int> offset(0, 0);
        update(offset);
    }

    void GUIObject::draw()
    {
        Pair<int, int> offset(0, 0);
        draw(offset);
    }

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

    Pair<int, int> GUIObject::getDrawPosition()
    {
        Pair<int, int> drawPosition;

        int xOffset = 0, yOffset = 0;
        switch (_anchor)
        {
        case GUIAnchor::TOP_LEFT:
            break;

        case GUIAnchor::TOP_MIDDLE:
            xOffset = -_objectDimensions.first / 2;
            break;

        case GUIAnchor::TOP_RIGHT:
            xOffset = -_objectDimensions.first;
            break;

        case GUIAnchor::MIDDLE_LEFT:
            yOffset = -_objectDimensions.second / 2;
            break;

        case GUIAnchor::MIDDLE:
            xOffset = -_objectDimensions.first / 2;
            yOffset = -_objectDimensions.second / 2;
            break;

        case GUIAnchor::MIDDLE_RIGHT:
            xOffset = -_objectDimensions.first;
            yOffset = -_objectDimensions.second / 2;
            break;

        case GUIAnchor::BOTTOM_LEFT:
            yOffset = -_objectDimensions.second;
            break;

        case GUIAnchor::BOTTOM_MIDDLE:
            xOffset = -_objectDimensions.first / 2;
            yOffset = -_objectDimensions.second;
            break;

        case GUIAnchor::BOTTOM_RIGHT:
            xOffset = -_objectDimensions.first;
            yOffset = -_objectDimensions.second;
            break;

        default:
            break;
        }

        drawPosition.first = _anchorPosition.first + xOffset;
        drawPosition.second = _anchorPosition.second + yOffset;

        return drawPosition;
    }

}

