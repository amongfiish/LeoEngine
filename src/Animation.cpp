#include "LeoEngine/Animation.hpp"
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Logger.hpp"

namespace LeoEngine
{
    std::shared_ptr<Animation> createAnimationFromStripData(std::string filename, int cellWidth, int cellHeight, int numberOfCells, int displayTime)
    {
        if (numberOfCells < 0 || cellWidth < 0 || cellHeight < 0 || filename == "")
        {
            Services::get().getLogger()->error("Animation", "Attempting to create animation from invalid strip data.");
            return nullptr;
        }

        std::shared_ptr<Animation> newAnimation = std::make_shared<Animation>(filename, cellWidth, cellHeight);
    
        int x = 0;
        for (int i = 0; i < numberOfCells; i++)
        {
            AnimationFrameData newFrameData(x, 0, displayTime);
            newAnimation->addFrame(newFrameData);
            x += cellWidth;
        }

        return newAnimation;
    }

    Animation::Animation(std::string filename, int width, int height)
        : _filename(filename),
          _dimensions(width, height)
    {
        
    }

    Animation::~Animation()
    {
        
    }

    std::string Animation::getFilename() const
    {
        return _filename;
    }

    const Pair<int, int> &Animation::getDimensions() const
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

    int Animation::getNumberOfFrames() const
    {
        return _frameData.size();
    }

    void Animation::addFrame(int sheetX, int sheetY, int displayTime)
    {
        _frameData.emplace_back(sheetX, sheetY, displayTime);   
    }

    void Animation::addFrame(AnimationFrameData& frameData)
    {
        addFrame(frameData.sheetX, frameData.sheetY, frameData.displayTime);
    }

}
