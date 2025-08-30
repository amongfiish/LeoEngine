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

        virtual void onActivate() {};
        virtual void onDeactivate() {};

        virtual void update(double deltaTime) = 0;
        virtual void draw() = 0;
    };

}

#endif

