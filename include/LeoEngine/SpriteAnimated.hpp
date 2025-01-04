#ifndef SPRITE_ANIMATED_HPP
#define SPRITE_ANIMATED_HPP

#include <memory>
#include "LeoEngine/Animation.hpp"
#include "LeoEngine/SpriteStatic.hpp"
using namespace std;

namespace LeoEngine
{

    class SpriteAnimated
    {
    public:
        SpriteAnimated();
        ~SpriteAnimated();

        void update();
        void draw();

        void setAnimation(shared_ptr<Animation> animation);

        void pauseAnimation();
        void unpauseAnimation();
        void restartAnimation();

        void setCurrentFrame(int frame);

        void setLoop(bool shouldLoop);

        // hmm...
        SpriteStatic &getSprite();

    private:
        void fetchFrameData();

        shared_ptr<Animation> _animation;

        SpriteStatic _sprite;

        bool _loop;
        bool _paused;

        int _startFrame;
        int _currentFrame;
        int _currentFrameTimer;
    };

}

#endif
