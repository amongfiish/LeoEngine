#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <vector>
#include <stdexcept>
#include <memory>
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Logger.hpp"
#include "LeoEngine/Part.hpp"
using namespace std;

namespace LeoEngine
{

    // a collection of Parts
    class Object
    {
    public:
        Object() = default;

        ~Object()
        {
            _parts.clear();
        }

        void update()
        {
            for (auto itPart = _parts.begin(); itPart != _parts.end(); itPart++) 
            {
                (*itPart)->update();
            }
        }

        void draw()
        {
            for (auto itPart = _parts.begin(); itPart != _parts.end(); itPart++)
            {
                (*itPart)->draw();
            }
        }

        template<class T>
        shared_ptr<T> addPart()
        {
            shared_ptr<T> newPart = make_shared<T>();
            shared_ptr<Part> castedNewPart = dynamic_pointer_cast<Part>(newPart);
            if (castedNewPart == nullptr)
            {
                Services::get().getLogger()->error("Object", "Attempting to add non-part to an object.");
                return nullptr;
            }

            _parts.push_back(castedNewPart);

            return newPart;
        }

        template<class T>
        shared_ptr<T> getPart()
        {
            for (auto itPart = _parts.begin(); itPart != _parts.end(); itPart++)
            {
                shared_ptr<T> castedPart = dynamic_pointer_cast<T>(*itPart);
                if (castedPart != nullptr)
                {
                    return castedPart;
                }
            }

            Services::get().getLogger()->error("Object", "Attempting to retrieve part that doesn't exist in object.");
            return nullptr;
        }

        template<class T>
        void removePart()
        {
            for (auto itPart = _parts.begin(); itPart != _parts.end(); itPart++)
            {
                shared_ptr<T> castedPart = dynamic_pointer_cast<T>(*itPart);
                if (castedPart != nullptr)
                {
                    _parts.erase(itPart);
                    return;
                }
            }
        }

    private:
        vector<shared_ptr<Part>> _parts;
    };

}

#endif

