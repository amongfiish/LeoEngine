#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <vector>
#include <string>
#include <stdexcept>
#include "LeoEngine/Pair.hpp"
#include "LeoEngine/Rectangle.hpp"
#include "LeoEngine/Circle.hpp"
#include "LeoEngine/Collision.hpp"
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Logger.hpp"

namespace LeoEngine
{

    template <typename T>
    class Quadtree
    {
    public:
        Quadtree(Rectangle<int> bounds, int maxElements)
            : _topLeft(nullptr), _topRight(nullptr),
              _bottomLeft(nullptr), _bottomRight(nullptr),
              _bounds(bounds), _maxElements(maxElements)
        {

        }

        ~Quadtree()
        {
            if (_topLeft != nullptr)
            {
                delete _topLeft;
            }
            if (_topRight != nullptr)
            {
                delete _topRight;
            }
            if (_bottomLeft != nullptr)
            {
                delete _bottomLeft;
            }
            if (_bottomRight != nullptr)
            {
                delete _bottomRight;
            }
        }

        template <typename U>
        void insert(T* element, U bounds)
        {
            if (!checkForOverlap(_bounds, bounds))
            {
                std::string errorMessage = "Requesting insertion of element that is not contained within _bounds.";
                Services::get().getLogger()->error("Quadtree", errorMessage);
                Services::get().getLogger()->flush();
                throw std::runtime_error(errorMessage);
            }

            if (_elements.size() < _maxElements || (_topLeft == nullptr && (_bounds.width/2 <= 1)))
            {
                
            }

            if (_elements.size() == _maxElements && _topLeft != nullptr)
            {
                
            }

            if (_topLeft != nullptr)
            {
                if (checkForOverlap(_bounds, _topLeft->_bounds))
                {
                    _topLeft->insert(element, bounds);
                }
                if (checkForOverlap(_bounds, _topLeft->_bounds))
                {
                    _topLeft->insert(element, bounds);
                }
                if (checkForOverlap(_bounds, _topLeft->_bounds))
                {
                    _topLeft->insert(element, bounds);
                }
                if (checkForOverlap(_bounds, _topLeft->_bounds))
                {
                    _topLeft->insert(element, bounds);
                }
            }
        }

    private:
        Rectangle<int> _bounds;

        std::vector<T*> _elements;
        int _maxElements;

        Quadtree<T>* _topLeft;
        Quadtree<T>* _topRight;
        Quadtree<T>* _bottomLeft;
        Quadtree<T>* _bottomRight;
    };

}

#endif

