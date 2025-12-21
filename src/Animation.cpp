#include "LeoEngine/Animation.hpp"
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Logger.hpp"

namespace LeoEngine
{
    std::shared_ptr<Animation> createAnimationFromStripData(std::string filename, int cellWidth, int cellHeight, int numberOfCells, double displayTime, int numberOfCellsPerRow)
    {
        if (numberOfCells < 0 || cellWidth < 0 || cellHeight < 0 || filename == "" || numberOfCellsPerRow == 0)
        {
            std::string errorMessage = "Attempting to create animation from invalid strip data.";
            Services::get().getLogger()->error("Animation", errorMessage);
            Services::get().getLogger()->flush();
            throw std::runtime_error(errorMessage);
        }

        std::shared_ptr<Animation> newAnimation = std::make_shared<Animation>(filename, cellWidth, cellHeight);
    
        int x = 0, y = 0;
        int processedCells = 0;
        while (processedCells < numberOfCells)
        {
            if (numberOfCellsPerRow < 0)
            {
                numberOfCellsPerRow = numberOfCells;
            }

            for (int i = 0; i < numberOfCellsPerRow; i++)
            {
                AnimationFrameData newFrameData(x, y, displayTime);
                newAnimation->addFrame(newFrameData);
                x += cellWidth;

                processedCells++;
                if (processedCells == numberOfCells)
                {
                    break;
                }
            }

            x = 0;
            y += cellHeight;
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
            std::string errorMessage = "Frame number provided was out of range.";
            Services::get().getLogger()->error("Animation", errorMessage);
            Services::get().getLogger()->flush();
            throw std::runtime_error(errorMessage);
        }

        return _frameData.at(frame);
    }

    int Animation::getNumberOfFrames() const
    {
        return static_cast<int>(_frameData.size());
    }

    void Animation::addFrame(int sheetX, int sheetY, double displayTime)
    {
        _frameData.emplace_back(sheetX, sheetY, displayTime);   
    }

    void Animation::addFrame(AnimationFrameData& frameData)
    {
        addFrame(frameData.sheetX, frameData.sheetY, frameData.displayTime);
    }

}
