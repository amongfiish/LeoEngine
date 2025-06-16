#include "LeoEngine/SceneTest.hpp"
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Graphics.hpp"

namespace LeoEngine
{

    SceneTest::SceneTest()
        : _fillColour(0x00, 0x00, 0xFF, 0xFF),
          _outlineColour(0xFF, 0x00, 0x00, 0xFF)
    {

    }

    SceneTest::~SceneTest()
    {

    }

    void SceneTest::onActivate()
    {

    }

    void SceneTest::onDeactivate()
    {

    }

    void SceneTest::update()
    {
        Pair<int, int> windowDimensions = Services::get().getGraphics()->getWindowDimensions();

        _rectangle.width = windowDimensions.first;
        _rectangle.height = windowDimensions.second;
    }

    void SceneTest::draw()
    {
        Services::get().getGraphics()->drawRectangle(_fillColour, true, _rectangle);
        Services::get().getGraphics()->drawRectangle(_outlineColour, false, _rectangle);
    }

}

