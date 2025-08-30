#ifndef SPRITE_ANIMATED_HPP
#define SPRITE_ANIMATED_HPP

#include <memory>
#include "LeoEngine/Animation.hpp"
#include "LeoEngine/SpriteStatic.hpp"

namespace LeoEngine
{

    class SpriteAnimated
    {
    public:
        SpriteAnimated();
        ~SpriteAnimated();

        void update(double deltaTime);
        void draw();

        void setAnimation(std::shared_ptr<Animation> animation);

        void pauseAnimation();
        void unpauseAnimation();
        void restartAnimation();

        void setCurrentFrame(int frame);

        void setLoop(bool shouldLoop);

        // hmm...
        SpriteStatic &getSprite();

    private:
        void fetchFrameData();

        std::shared_ptr<Animation> _animation;

        SpriteStatic _sprite;

        bool _loop;
        bool _paused;

        int _startFrame;
        int _currentFrame;
        double _currentFrameTimer;
    };

}

#endif
