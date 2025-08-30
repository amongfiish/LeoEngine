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

        virtual void onActivate() override;
        virtual void onDeactivate() override;

        virtual void update(double deltaTime) override;
        virtual void draw() override;

    private:
        Rectangle<int> _rectangle;
        Colour _fillColour;
        Colour _outlineColour;
    };

}

#endif

