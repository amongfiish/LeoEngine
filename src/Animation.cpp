#include "Animation.hpp"
#include "Services.hpp"
#include "Logger.hpp"

Animation::Animation(string filename, int width, int height)
    : _filename(filename),
      _dimensions(width, height)
{

}

Animation::~Animation()
{
    
}

const Pair<int, int>& Animation::getDimensions() const
{
    return _dimensions;
}

const AnimationFrameData Animation::getFrameData(int frame) const
{
    if (frame < 0 || frame >= _frameData.size())
    {
        Services::get().getLogger()->error("Animation", "Frame number provided was out of range.");

        return AnimationFrameData(-1, -1, -1);
    }

    return _frameData[frame];
}

void Animation::addFrame(int sheetX, int sheetY, int displayTime)
{
    _frameData.emplace_back(sheetX, sheetY, displayTime);   
}

void Animation::addFrame(AnimationFrameData& frameData)
{
    addFrame(frameData.sheetX, frameData.sheetY, frameData.displayTime);
}

