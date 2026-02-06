#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

namespace LeoEngine
{

    class Drawable
    {
    public:
        virtual ~Drawable() {};

        virtual void update(double deltaTime) {}
        virtual void draw() = 0;
    };

}

#endif

