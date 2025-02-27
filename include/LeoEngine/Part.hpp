#ifndef PART_HPP
#define PART_HPP

namespace LeoEngine
{

    // an Object is made up by any number of these
    class Part
    {
    public:
        virtual ~Part() {}

        virtual void update() {}
        virtual void draw() {}

        virtual void reset() {}

    protected:
        Part() = default;
    };

}

#endif

