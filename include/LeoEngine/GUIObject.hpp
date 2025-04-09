#ifndef GUI_OBJECT_HPP
#define GUI_OBJECT_HPP

#include "LeoEngine/Pair.hpp"
#include "LeoEngine/GUIAnchor.hpp"

namespace LeoEngine
{

    class GUIObject
    {
    public:
        GUIObject();
        virtual ~GUIObject();

        virtual void update() = 0;
        virtual void draw() = 0;

        void setAnchor(GUIAnchor anchor);

        void setAnchorPosition(int x, int y);
        void setAnchorPosition(Pair<int, int>& position);

    protected:
        Pair<int, int> getDrawPosition();

        GUIAnchor _anchor;
        Pair<int, int> _anchorPosition;

        Pair<int, int> _objectDimensions;
    };

}

#endif

