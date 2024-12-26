#ifndef OBJECT_COLLECTION_HPP
#define OBJECT_COLLECTION_HPP

#include <map>
#include "LeoEngine/Object.hpp"
using namespace std;

namespace LeoEngine
{

    // tracks and updates all objects
    class ObjectCollection
    {
    public:
        ObjectCollection();
        ~ObjectCollection();

        void update();
        void draw();

        Object *add();
        void destroy(int id);

    private:
        map<int, Object> _objects;
        int _nextID = 0;
    };

}

#endif

