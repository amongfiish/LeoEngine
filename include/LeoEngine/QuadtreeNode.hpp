#ifndef QUADTREE_NODE_HPP
#define QUADTREE_NODE_HPP

#include <vector>
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Logger.hpp"

namespace LeoEngine
{

    template <typename T>
    class QuadtreeNode
    {
    public:
        QuadtreeNode()
        {
            for (int i = 0; i < 4; i++)
            {
                _childNodes[i] = nullptr;
            }
        }
    
        ~QuadtreeNode()
        {
            for (int i = 0; i < 4; i++)
            {
                if (_childNodes[i] != nullptr)
                {
                    delete _childNodes[i];
                }
            }
        }

        void add(T* e)
        {

        }

        void clear()
        {
            _elements.clear();
        }

        QuadtreeNode* getChildNode(int i)
        {
            if (i < 0 || i >= 4)
            {
                std::string errorMessage = "Index #" + std::to_string(i) + " is out of range (4).";
                LeoEngine::Services::get().getLogger()->error("QuadtreeNode", errorMessage);
                LeoEngine::Services::get().getLogger()->flush();
                throw std::runtime_error(errorMessage);
            }

            return _childNodes[i];
        }

        std::vector<T*> getElements()
        {
            return _elements;
        }

        std::vector<T*> getElementsFromChildren()
        {
            std::vector<T*> elements;

            for (int i = 0; i < 4; i++)
            {
                if (_childNodes[i] == nullptr)
                {
                    break;
                }

                std::vector<T*> childElements = _childNodes[i].getElements();
                std::vector<T*> childChildrenElements = _childNodes[i].getElementsFromChildren();
                elements.insert(elements.end(), childElements.begin(), childElements.end());
                elements.insert(elements.end(), childChildrenElements.begin(), childChildrenElements.end());
            }
        }

    private:
        QuadtreeNode* _childNodes[4];
        std::vector<T*> _elements;
    };

}

#endif

