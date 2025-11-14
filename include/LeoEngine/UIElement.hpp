#ifndef UI_ELEMENT_HPP
#define UI_ELEMENT_HPP

#include <stdexcept>
#include <string>
#include <vector>

#include "LeoEngine/Services.hpp"
#include "LeoEngine/Logger.hpp"
#include "LeoEngine/Rectangle.hpp"
#include "LeoEngine/Pair.hpp"

namespace LeoEngine
{

    enum class UIAnchor
    {
        TOP_LEFT,
        TOP_MIDDLE,
        TOP_RIGHT,
        MIDDLE_LEFT,
        MIDDLE,
        MIDDLE_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_MIDDLE,
        BOTTOM_RIGHT
    };

    class UIElement
    {
    public:
        UIElement();
        virtual ~UIElement();

        void setPosition(int x, int y);
        void setPosition(const Pair<int, int>& _position);

        template<typename T>
        T *createChild();

        void activate();
        void deactivate();

        void update();
        void draw();

    protected:
        virtual void updateInternal() {};
        virtual void drawInternal() {};

        // get the global bounds (starting from top left corner) of the element
        Rectangle<int> getGlobalBounds() const;

        const UIElement *_parent;
        std::vector<UIElement *> _children;

        bool _isActive;

        UIAnchor _anchor;   // where (on the parent) to anchor the origin
        UIAnchor _origin;   // where (on this object) to consider the origin

        Rectangle<int> _bounds; // x,y is the offset from the origin;
                                // w,h is the dimensions of the object
                                // (to be set by the object itself)
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

