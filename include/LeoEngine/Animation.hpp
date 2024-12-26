#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <string>
#include <vector>
#include "LeoEngine/Pair.hpp"
using namespace std;

namespace LeoEngine
{

    struct AnimationFrameData
    {
        AnimationFrameData(int sheetX, int sheetY, int displayTime)
            : sheetX(sheetX), sheetY(sheetY), displayTime(displayTime)
        {
        }

        // location of sprite origin in sprite sheet
        int sheetX;
        int sheetY;

        // # of frames that the sprite should be displayed for
        int displayTime;
    };

    class Animation
    {
    public:
        Animation(string filename, int width, int height);
        ~Animation();

        const Pair<int, int> &getDimensions() const;
        const AnimationFrameData getFrameData(int frame) const;

        void addFrame(int sheetX, int sheetY, int displayTime);
        void addFrame(AnimationFrameData &frameData);

    private:
        string _filename;

        vector<AnimationFrameData> _frameData;
        Pair<int, int> _dimensions;
    };

}

#endif

