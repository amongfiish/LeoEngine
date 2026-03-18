#include "LeoEngine/CameraStatic.hpp"

namespace LeoEngine
{

    CameraStatic::CameraStatic()
    {
        setPosition(0, 0);
    }

    CameraStatic::CameraStatic(int x, int y)
    {
        setPosition(x, y);
    }

    CameraStatic::CameraStatic(Pair<int, int>& position)
    {
        setPosition(position);
    }

    CameraStatic::~CameraStatic()
    {

    }

    void CameraStatic::update()
    {

    }

}
