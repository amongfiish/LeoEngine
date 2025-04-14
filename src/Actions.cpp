#include "LeoEngine/Actions.hpp"

namespace LeoEngine
{

    Actions::Actions()
    {

    }

    Actions::~Actions()
    {

    }

    void Actions::addActionSequence(ActionSequence actionSequence)
    {
        _actionSequences.push_back(actionSequence);
    }

}

