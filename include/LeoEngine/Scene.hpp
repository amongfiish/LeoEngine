#ifndef SCENE_HPP
#define SCENE_HPP

namespace LeoEngine
{

    class Scene
    {
    public:
        Scene()
        {
        }
        virtual ~Scene()
        {
        }

        virtual void update() = 0;
        virtual void draw() = 0;
    };

}

#endif

