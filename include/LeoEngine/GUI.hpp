#ifndef GUI_HPP
#define GUI_HPP

#include <vector>
#include <memory>
#include "LeoEngine/Pair.hpp"
#include "LeoEngine/GUIObject.hpp"

namespace LeoEngine
{

    class GUI
    {
    public:
        GUI()
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

        void setPosition(double x, double y)
        {
            _position.first = x;
            _position.second = y;
        }

        void setPosition(Pair<double, double>& position)
        {
            _position.first = position.first;
            _position.second = position.second;
        }

        template<class T>
        void addObject()
        {
            _guiObjects.push_back(make_shared<T>());
        }

    private:
        Pair<double, double> _position;

        std::vector<std::shared_ptr<GUIObject>> _guiObjects;
    };

}

#endif

