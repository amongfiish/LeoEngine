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
#include "LeoEngine/Graphics.hpp"

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

            if (_elements.size() == _maxElements && _topLeft == nullptr && _bounds.width >= 2)
            {
                // subdivide
                _subdivide();
            }

            if (_topLeft != nullptr)
            {
                if (checkForOverlap(_topLeft->_bounds, bounds))
                {
                    _topLeft->insert(element, bounds);
                }
                if (checkForOverlap(_topRight->_bounds, bounds))
                {
                    _topRight->insert(element, bounds);
                }
                if (checkForOverlap(_bottomLeft->_bounds, bounds))
                {
                    _bottomLeft->insert(element, bounds);
                }
                if (checkForOverlap(_bottomRight->_bounds, bounds))
                {
                    _bottomRight->insert(element, bounds);
                }
            }
            else
            {
                _elements.push_back(element);
            }
        }

        void clear()
        {
            _elements.clear();

            if (_topLeft != nullptr)
            {
                delete _topLeft;
                delete _topRight;
                delete _bottomLeft;
                delete _bottomRight;

                _topLeft = nullptr;
                _topRight = nullptr;
                _bottomLeft = nullptr;
                _bottomRight = nullptr;
            }
        }

        void draw()
        {
            static Colour BOX_COLOUR(0x00, 0x00, 0xFF, 0xFF);
            Services::get().getGraphics()->drawRectangle(BOX_COLOUR, false, _bounds);

            if (_topLeft != nullptr)
            {
                _topLeft->draw();
                _topRight->draw();
                _bottomLeft->draw();
                _bottomRight->draw();
            }
        }

        Quadtree<T>* getTopLeft()
        {
            return _topLeft;
        }

        Quadtree<T>* getTopRight()
        {
            return _topRight;
        }

        Quadtree<T>* getBottomLeft()
        {
            return _bottomLeft;
        }

        Quadtree<T>* getBottomRight()
        {
            return _bottomRight;
        }

        std::vector<T*>& getElements()
        {
            return _elements;
        }

        template <typename U>
        std::vector<T*> getPotentialOverlaps(U bound)
        {
            std::vector<T*> elements;
            
            if (checkForOverlap(_bounds, bound))
            {
                if (_topLeft != nullptr)
                {
                    if (checkForOverlap(_topLeft->bounds, bound))
                    {
                        std::vector<T*> topLeftElements = _topLeft->getPotentialOverlaps(bound);
                        elements.insert(elements.end(), topLeftElements.begin(), topLeftElements.end());
                    }
                    if (checkForOverlap(_topRight->bounds, bound))
                    {
                        std::vector<T*> topRightElements = _topRight->getPotentialOverlaps(bound);
                        elements.insert(elements.end(), topRightElements.begin(), topRightElements.end());
                    }
                    if (checkForOverlap(_bottomLeft->bounds, bound))
                    {
                        std::vector<T*> bottomLeftElements = _bottomLeftElements->getPotentialOverlaps(bound);
                        elements.insert(elements.end(), bottomLeftElements.begin(), bottomLeftElements.end());
                    }
                    if (checkForOverlap(_bottomRight->bounds, bound))
                    {
                        std::vector<T*> bottomRightElements = _bottomRightElements->getPotentialOverlaps(bound);
                        elements.insert(elements.end(), bottomRightElements.begin(), bottomRightElements.end());
                    }
                }
                else
                {
                    return _elements;
                }
            }

            return elements;
        }

    private:
        void _subdivide()
        {
            if (_topLeft != nullptr)
            {
                std::string errorMessage = "Attempting to subdivide an already subdivided quadtree node.";
                Services::get().getLogger()->error("Quadtree", errorMessage);
                Services::get().getLogger()->flush();
                throw std::runtime_error(errorMessage);
            }

            _topLeft = new Quadtree(LeoEngine::Rectangle<int>(_bounds.x, _bounds.y, _bounds.width/2, _bounds.height/2), _maxElements);
            _topRight = new Quadtree(LeoEngine::Rectangle<int>(_bounds.x + _bounds.width/2, _bounds.y, _bounds.width/2, _bounds.height/2), _maxElements);
            _bottomLeft = new Quadtree(LeoEngine::Rectangle<int>(_bounds.x, _bounds.y + _bounds.height/2, _bounds.width/2, _bounds.height/2), _maxElements);
            _bottomRight = new Quadtree(LeoEngine::Rectangle<int>(_bounds.x + _bounds.width/2, _bounds.y + _bounds.height/2, _bounds.width/2, _bounds.height/2), _maxElements);
        }

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

