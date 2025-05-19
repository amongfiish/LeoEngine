#ifndef ACTION_SEQUENCE_HPP
#define ACTION_SEQUENCE_HPP

#include <vector>
#include <memory>
#include "LeoEngine/Action.hpp"
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Logger.hpp"

namespace LeoEngine
{

    // stores a vector of actions to be executed in sequence.
    // can be looped. can call a callback function when complete.
    class ActionSequence
    {
    public:
        ActionSequence()
            : _currentAction(0)
        {

        }

        ~ActionSequence()
        {

        }

        template<class T>
        void addAction()
        {
            std::shared_ptr<T> newT = std::make_shared<T>();
            if (newT == nullptr)
            {
                Services::get().getLogger()->error("ActionSequence", "Failed to add new action.");
                return;
            }

            _actions.push_back(newT);
        }

        void execute()
        {
            if (!_actions.empty())
            {
                bool executionResult = _actions.at(_currentAction)->execute();
                if (executionResult)
                {
                    _currentAction = (_currentAction + 1) % _actions.size();
                }
            }
        }

    private:
        std::vector<std::shared_ptr<Action>> _actions;
        int _currentAction;
    };

}

#endif

