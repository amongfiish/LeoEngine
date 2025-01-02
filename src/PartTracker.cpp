#include "LeoEngine/PartTracker.hpp"

namespace LeoEngine
{

    PartTracker::PartTracker()
        : _subject(nullptr),
          _follower(nullptr),
          _offsetX(0),
          _offsetY(0)
    {

    }

    PartTracker::~PartTracker()
    {

    }

    void PartTracker::setSubject(shared_ptr<PartTransform> subject)
    {
        _subject = subject;
    }

    void PartTracker::setFollower(shared_ptr<PartTransform> follower)
    {
        _follower = follower;
    }

    void PartTracker::setOffset(int x, int y)
    {
        _offsetX = x;
        _offsetY = y;
    }

    void PartTracker::setOffset(const Pair<int, int> &offset)
    {
        setOffset(offset.first, offset.second);
    }

    void PartTracker::update()
    {
        if (_subject == nullptr || _follower == nullptr)
        {
            return;
        }

        const Pair<double, double> &subjectPosition = _subject->getPosition();
        _follower->setPosition(subjectPosition.first + _offsetX, subjectPosition.second + _offsetY);
    }

}
