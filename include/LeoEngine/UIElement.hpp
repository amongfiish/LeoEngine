#ifndef UI_ELEMENT_HPP
#define UI_ELEMENT_HPP

#include <stdexcept>
#include <string>
#include <vector>
#include <memory>

#include "LeoEngine/Services.hpp"
#include "LeoEngine/Logger.hpp"
#include "LeoEngine/Rectangle.hpp"

namespace LeoEngine
{

    class UIElement
    {
    public:
        UIElement();
        virtual ~UIElement();

        template<typename T>
        T *createChild();

        virtual void update() {}
        virtual void draw() = 0;

    protected:
        const UIElement *_parent;
        std::vector<UIElement *> _children;

        // used for drawing 
        bool _isVisible;
        Rectangle<int> _bounds;
    };

    template<typename T>
    T *UIElement::createChild()
    {
        T *newElement = new T;
        UIElement *castElement = dynamic_cast<UIElement *>(newElement);
        if (castElement == nullptr)
        {
            std::string errorMessage = "Attempting to add non UIElement-derived class as a child of a UIElement.";
            Services::get().getLogger()->error("UIElement", errorMessage);
            throw std::runtime_error(errorMessage);
        }

        castElement->_parent = this;
        _children.push_back(castElement);

        return newElement;
    }

}

#endif

