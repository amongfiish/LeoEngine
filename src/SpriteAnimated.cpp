#include "LeoEngine/SpriteAnimated.hpp"
#include "LeoEngine/Rectangle.hpp"

namespace LeoEngine
{

    SpriteAnimated::SpriteAnimated()
        : _animation(nullptr),
        _currentFrame(0),
        _currentFrameTimer(0),
        _paused(false),
        _loop(true),
        _startFrame(0)
    {

    }

    SpriteAnimated::~SpriteAnimated()
    {

    }

    void SpriteAnimated::update()
    {
        if (_animation == nullptr || _paused)
        {
            return;
        }

        if (_currentFrameTimer <= 0)
        {
            _currentFrame = (_currentFrame + 1) % _animation->getNumberOfFrames();
            
            if (!_loop && _currentFrame == _startFrame)
            {
                pauseAnimation();
            }
            else
            {
                fetchFrameData();
            }
        }
        else
        {
            _currentFrameTimer--;
        }
    }

    void SpriteAnimated::draw()
    {
        _sprite.draw();
    }

    void SpriteAnimated::setAnimation(std::shared_ptr<Animation> animation)
    {
        _animation = animation;

        if (_animation != nullptr)
        {
            restartAnimation();
        }
    }

    void SpriteAnimated::restartAnimation()
    {
        _currentFrame = _startFrame;
        unpauseAnimation();
        fetchFrameData();
    }

    void SpriteAnimated::pauseAnimation()
    {
        _paused = true;
    }

    void SpriteAnimated::unpauseAnimation()
    {
        _paused = false;
    }

    void SpriteAnimated::setCurrentFrame(int frame)
    {
        _currentFrame = frame;
        _startFrame = frame;
    }

    void SpriteAnimated::setLoop(bool shouldLoop)
    {
        _loop = shouldLoop;
    }

    SpriteStatic &SpriteAnimated::getSprite()
    {
        return _sprite;
    }

    void SpriteAnimated::fetchFrameData()
    {
        AnimationFrameData currentFrameData = _animation->getFrameData(_currentFrame);
        const Pair<int, int> &frameDimensions = _animation->getDimensions();

        _sprite.setTextureFilename(_animation->getFilename());
        _sprite.setSourceRectangle(std::make_shared<Rectangle<int>>(currentFrameData.sheetX, currentFrameData.sheetY, frameDimensions.first, frameDimensions.second));
        _currentFrameTimer = currentFrameData.displayTime;
    }

}
