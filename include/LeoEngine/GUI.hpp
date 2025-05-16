#ifndef GUI_HPP
#define GUI_HPP

#include <vector>
#include <memory>
#include "LeoEngine/Pair.hpp"
#include "LeoEngine/Rectangle.hpp"
#include "LeoEngine/GUIObject.hpp"
#include "LeoEngine/GUIAnchor.hpp"

namespace LeoEngine
{

    class GUI
    {
    public:
        GUI()
            : _bounds(0, 0, 0, 0),
            _drawOffset(0, 0),
            _anchor(GUIAnchor::TOP_LEFT)
        {

        }

        ~GUI()
        {

        }

        void update()
        {
            for (auto object : _guiObjects)
            {
                object->update(_position);
            }
        }

        void draw()
        {
            for (auto object: _guiObjects)
            {
                object->draw(_position);
            }
        }

        void setBounds(Rectangle& bounds)
        {
            _bounds.x = bounds.x;
            _bounds.y = bounds.y;
            _bounds.width = bounds.width;
            _bounds.height = bounds.height;

            updateDrawPosition();
        }

        void setAnchor(GUIAnchor anchor)
        {
            _anchor = anchor;

            updateDrawPosition();
        }

        template<class T>
        void addObject()
        {
            _guiObjects.push_back(make_shared<T>());
        }

    private:
        void updateDrawPosition()
        {
            switch (_anchor)
            {
            case GUIAnchor::TOP_LEFT:
                _drawOffset.first = 0;
                _drawOffset.second = 0;
                break;

            case GUIAnchor::TOP_MIDDLE:
                _drawOffset.first = _bounds.width / 2;
                _drawOffset.second = 0;
                break;

            case GUIAnchor::TOP_RIGHT:
                _drawOffset.first = _bounds.width;
                _drawOffset.second = 0;
                break;

            case GUIAnchor::MIDDLE_LEFT:
                _drawOffset.first = 0;
                _drawOffset.second = _bounds.height / 2;
                break;

            case GUIAnchor::MIDDLE:
                _drawOffset.first = _bounds.width / 2;
                _drawOffset.second = _bounds.height / 2;
                break;

            case GUIAnchor::MIDDLE_RIGHT:
                _drawOffset.first = _bounds.width;
                _drawOffset.second = _bounds.height / 2;
                break;

            case GUIAnchor::BOTTOM_LEFT:
                _drawOffset.first = 0;
                _drawOffset.second = _bounds.height;
                break;

            case GUIAnchor::BOTTOM_MIDDLE:
                _drawOffset.first = _bounds.width / 2;
                _drawOffset.second = _bounds.height;
                break;

            case GUIAnchor::BOTTOM_RIGHT:
                _drawOffset.first = _bounds.width;
                _drawOffset.second = _bounds.height;
                break;
            }
        }

        Rectangle _bounds;
        GUIAnchor _anchor;

        Pair<int, int> _drawOffset;

        std::vector<std::shared_ptr<GUIObject>> _guiObjects;
    };

}

#endif

