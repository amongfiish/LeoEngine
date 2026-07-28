#ifndef SPRITE_ANIMATED_HPP
#define SPRITE_ANIMATED_HPP

#include <memory>
#include "LeoEngine/Drawable.hpp"
#include "LeoEngine/Animation.hpp"
#include "LeoEngine/SpriteStatic.hpp"

namespace LeoEngine
{

    class SpriteAnimated : public Drawable
    {
    public:
        SpriteAnimated();
        virtual ~SpriteAnimated();

        virtual void update(double deltaTime) override;
        virtual void draw() override;

        void setAnimation(std::shared_ptr<Animation> animation);

        void pauseAnimation();
        void unpauseAnimation();
        void restartAnimation();

        void setCurrentFrame(int frame);

        void setLoop(bool shouldLoop);
        void setReverse(bool reverse);
        void setSpeed(float speed);

        // hmm...
        SpriteStatic &getSprite();

        bool isPaused() const;

    private:
        void fetchFrameData();

        std::shared_ptr<Animation> _animation;

        SpriteStatic _sprite;

        bool _loop;
        bool _reverse;
        bool _paused;
        float _speed;

        int _startFrame;
        int _currentFrame;
        double _currentFrameTimer;
    };

}

#endif
