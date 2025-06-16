#ifndef SCENE_TEST_HPP
#define SCENE_TEST_HPP

#include "LeoEngine/Scene.hpp"
#include "LeoEngine/Rectangle.hpp"
#include "LeoEngine/Colour.hpp"

namespace LeoEngine
{

    class SceneTest : public Scene
    {
    public:
        SceneTest();
        virtual ~SceneTest();

        virtual void onActivate();
        virtual void onDeactivate();

        virtual void update();
        virtual void draw();

    private:
        Rectangle _rectangle;
        Colour _fillColour;
        Colour _outlineColour;
    };

}

#endif

