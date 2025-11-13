#include "LeoEngine/UIElement.hpp"

namespace LeoEngine
{

    UIElement::UIElement()
        : _parent(nullptr)
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

}

