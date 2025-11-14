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

        void setBounds(const Rectangle<int>& bounds);
    };

}

#endif

