#include <cmath>

#include "LeoEngine/MouseUtility.hpp"
#include "LeoEngine/Pair.hpp"
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Graphics.hpp"
#include "LeoEngine/Input.hpp"

#ifdef _WIN32
#define M_PI 3.14
#endif

namespace LeoEngine
{

    double MouseUtility::getAngleBetweenWindowCenterAndMouse()
    {
        Pair<int, int> renderDimensions = Services::get().getGraphics()->getRenderDimensions();
        Pair<int, int> absoluteWindowCenter(renderDimensions.first / 2, renderDimensions.second / 2);

        const LeoEngine::Pair<int, int>& mousePosition = LeoEngine::Services::get().getInput()->getMousePosition();

        double angle = (atan2(mousePosition.second - absoluteWindowCenter.second, mousePosition.first - absoluteWindowCenter.first) * (180/M_PI)) + 90;

        return angle;
    }

}

