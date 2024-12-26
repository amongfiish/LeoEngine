#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <vector>
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
            for (auto part : _parts) {
                delete part;
            }

            _parts.clear();
        }

        void update()
        {
            for (auto part : _parts) {
                part->update();
            }
        }

        void draw()
        {
            for (auto part : _parts) {
                part->draw();
            }
        }

        template<class T>
        T *addPart()
        {
            T *newPart = new T;
            Part *castedNewPart = dynamic_cast<Part *>(newPart);
            if (castedNewPart == nullptr) {
                Services::get().getLogger()->error("Object", "Attempting to add non-part to parts.");
                return;
            }

            _parts.push_back(castedNewPart);

            return castedNewPart;
        }

    private:
        vector<Part *> _parts;
    };

}

#endif

