#include "LeoEngine/ObjectCollection.hpp"

namespace LeoEngine
{

    ObjectCollection::ObjectCollection()
    {

    }

    ObjectCollection::~ObjectCollection()
    {
        _objects.clear();
    }

    void ObjectCollection::update(double deltaTime)
    {
        for (auto& p : _objects)
        {
            p.second.update(deltaTime);
        }
    }

    void ObjectCollection::draw()
    {
        for (auto& p : _objects)
        {
            p.second.draw();
        }
    }

    Object *ObjectCollection::add()
    {
        _objects.emplace(_nextID++, Object());

        auto itLastPair = _objects.rbegin();
        return &((*itLastPair).second);
    }

    void ObjectCollection::destroy(int id)
    {
        _objects.erase(id);
    }

}
