#ifndef ACTION_HPP
#define ACTION_HPP

namespace LeoEngine
{

    // actions affect other objects in some way. for example,
    // an action may be used to tween a game object in some way.
    // this is a base class.
    class Action
    {
    public:
        virtual ~Action() {}

        virtual bool execute() = 0;
    };

}

#endif

