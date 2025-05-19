#include "LeoEngine/Actions.hpp"

namespace LeoEngine
{

    Actions::Actions()
    {

    }

    Actions::~Actions()
    {

    }

    void Actions::update()
    {
        for (auto it = _actionSequences.begin(); it != _actionSequences.end(); it++)
        {
            it->execute();
        }
    }

    void Actions::addActionSequence(ActionSequence actionSequence)
    {
        _actionSequences.push_back(actionSequence);
    }

}

