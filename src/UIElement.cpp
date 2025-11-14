#include "LeoEngine/UIElement.hpp"

namespace LeoEngine
{

    UIElement::UIElement()
        : _parent(nullptr),
          _isActive(true),
          _bounds(0,0,0,0)
    {

    }

    UIElement::~UIElement()
    {
        for (auto& child : _children)
        {
            delete child;
            child = nullptr;
        }

        _children.clear();
    }

    void UIElement::setPosition(int x, int y)
    {
        _bounds.x = x;
        _bounds.y = y;
    }

    void UIElement::setPosition(const Pair<int, int>& position)
    {
        setPosition(position.first, position.second);
    }

    void UIElement::activate()
    {
        _isActive = true;
    }

    void UIElement::deactivate()
    {
        _isActive = false;
    }

    void UIElement::update()
    {
        if (_isActive)
        {
            updateInternal();
        }
    }

    void UIElement::draw()
    {
        if (_isActive)
        {
            drawInternal();
        }
    }

    void offsetWithAnchor(Rectangle<int>& originalRect, Rectangle<int> offsetRect, UIAnchor anchor)
    {
        switch (anchor)
        {
        case UIAnchor::TOP_LEFT:
            break;
        case UIAnchor::TOP_MIDDLE:
            originalRect.x += offsetRect.width / 2;
            break;
        case UIAnchor::TOP_RIGHT:
            originalRect.x += offsetRect.width;
            break;
        case UIAnchor::MIDDLE_LEFT:
            originalRect.y += offsetRect.height / 2;
            break;
        case UIAnchor::MIDDLE:
            originalRect.x += offsetRect.width / 2;
            originalRect.y += offsetRect.height / 2;
            break;
        case UIAnchor::MIDDLE_RIGHT:
            originalRect.x += offsetRect.width;
            originalRect.y += offsetRect.height / 2;
            break;
        case UIAnchor::BOTTOM_LEFT:
            originalRect.y += offsetRect.height;
            break;
        case UIAnchor::BOTTOM_MIDDLE:
            originalRect.x += offsetRect.width / 2;
            originalRect.y += offsetRect.height;
            break;
        case UIAnchor::BOTTOM_RIGHT:
            originalRect.x += offsetRect.width;
            originalRect.y += offsetRect.height;
            break;
        default:
            break;
        }
    }

    Rectangle<int> UIElement::getGlobalBounds() const
    {
        Rectangle<int> globalBounds(0, 0, 0, 0);

        if (_parent != nullptr)
        {
            Rectangle<int> parentBounds = _parent->getGlobalBounds();

            globalBounds.x += parentBounds.x;
            globalBounds.y += parentBounds.y;
            offsetWithAnchor(globalBounds, parentBounds, _anchor);
        }

        globalBounds.x += _bounds.x;
        globalBounds.y += _bounds.y;
        offsetWithAnchor(globalBounds, -_bounds, _origin);

        return globalBounds;
    }

}

