#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <vector>
#include "Services.hpp"
#include "Logger.hpp"
#include "Part.hpp"
using namespace std;

// a collection of Parts
class Object
{
public:
    Object() = default;

    ~Object()
    {
        for (auto part : _parts)
        {
            delete part;
        }

        _parts.clear();
    }

private:
    template<class T>
    T *addPart()
    {
        T *newPart = new T;
        Part *castedNewPart = dynamic_cast<Part *>(newPart);
        if (castedNewPart == nullptr)
        {
            Services::get().getLogger()->error("Object", "Attempting to add non-part to parts.");
            return;
        }

        _parts.push_back(castedNewPart);

        return castedNewPart;
    }

    vector<Part *> _parts;
};

#endif

