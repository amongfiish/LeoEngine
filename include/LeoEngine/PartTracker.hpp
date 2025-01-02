#ifndef PART_TRACKER_HPP
#define PART_TRACKER_HPP

#include <memory>
#include "LeoEngine/Part.hpp"
#include "LeoEngine/PartTransform.hpp"

namespace LeoEngine
{
    
    class PartTracker : public Part
    {
    public:
        PartTracker();
        virtual ~PartTracker();

        void setSubject(shared_ptr<PartTransform> subject);
        void setFollower(shared_ptr<PartTransform> follower);

        void setOffset(int x, int y);
        void setOffset(const Pair<int, int>& offset);

        virtual void update();

    private:
        shared_ptr<PartTransform> _subject;
        shared_ptr<PartTransform> _follower;

        int _offsetX;
        int _offsetY;
    };

}

#endif
