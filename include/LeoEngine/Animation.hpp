#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <string>
#include <vector>
#include <memory>
#include "LeoEngine/Pair.hpp"

namespace LeoEngine
{

    class Animation;

    std::shared_ptr<Animation> createAnimationFromStripData(std::string filename, int cellWidth, int cellHeight, int numberOfCells, double displayTime);

    struct AnimationFrameData
    {
        AnimationFrameData(int sheetX, int sheetY, double displayTime)
            : sheetX(sheetX), sheetY(sheetY), displayTime(displayTime)
        {
            
        }

        // location of sprite origin in sprite sheet
        int sheetX;
        int sheetY;

        // # of frames that the sprite should be displayed for
        double displayTime;
    };

    class Animation
    {
    public:
        Animation(std::string filename, int width, int height);
        ~Animation();

        std::string getFilename() const;
        const Pair<int, int> &getDimensions() const;
        const AnimationFrameData getFrameData(int frame) const;

        int getNumberOfFrames() const;

        void addFrame(int sheetX, int sheetY, double displayTime);
        void addFrame(AnimationFrameData &frameData);

    private:
        std::string _filename;

        std::vector<AnimationFrameData> _frameData;
        Pair<int, int> _dimensions;
    };

}

#endif

