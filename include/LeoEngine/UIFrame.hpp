#ifndef UI_FRAME_HPP
#define UI_FRAME_HPP

#include "LeoEngine/UIElement.hpp"

namespace LeoEngine
{

    class UIFrame : public UIElement
    {
    public:
        UIFrame();
        virtual ~UIFrame();

        // UIFrame has the dimensions of the render area
        // as its own dimensions by default
        void setSize(const Pair<int, int>& size);
    };

}

#endif

