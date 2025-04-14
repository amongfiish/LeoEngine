#ifndef ACTIONS_HPP
#define ACTIONS_HPP

#include <vector>
#include "LeoEngine/ActionSequence.hpp"

namespace LeoEngine
{

    // the actions service. executes actions provided by the game.
    class Actions
    {
    public:
        Actions();
        ~Actions();

        void update();

        // copies the sequence, so it can be used as a 'template'
        // in multiple different objects
        void addActionSequence(ActionSequence actionSequence);

    private:
        std::vector<ActionSequence> _actionSequences;
    };

}

#endif

