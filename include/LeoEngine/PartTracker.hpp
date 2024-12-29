#ifndef PART_TRACKER_HPP
#define PART_TRACKER_HPP

#include "LeoEngine/Part.hpp"
#include "LeoEngine/PartTransform.hpp"

namespace LeoEngine
{
    
    class PartTracker : public Part
    {
    public:
        PartTracker();
        virtual ~PartTracker();

        void setSubject(PartTransform *subject);
        void setFollower(PartTransform *follower);

        void setOffset(int x, int y);
        void setOffset(const Pair<int, int>& offset);

        virtual void update();

    private:
        PartTransform *_subject;
        PartTransform *_follower;

        int _offsetX;
        int _offsetY;
    };

}

#endif
