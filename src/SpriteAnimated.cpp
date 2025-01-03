#include "LeoEngine/SpriteAnimated.hpp"
#include "LeoEngine/Rectangle.hpp"

namespace LeoEngine
{

    SpriteAnimated::SpriteAnimated()
        : _animation(nullptr),
        _currentFrame(0),
        _currentFrameTimer(0),
        _paused(false)
    {

    }

    SpriteAnimated::~SpriteAnimated()
    {

    }

    void SpriteAnimated::update()
    {
        if (_animation == nullptr)
        {
            return;
        }

        if (_currentFrameTimer <= 0)
        {
            _currentFrame = (_currentFrame + 1) % _animation->getNumberOfFrames();
            fetchFrameData();
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

    void SpriteAnimated::setAnimation(shared_ptr<Animation> animation)
    {
        _animation = animation;

        if (_animation != nullptr)
        {
            restartAnimation();
            fetchFrameData();
        }
    }

    void SpriteAnimated::restartAnimation()
    {
        _currentFrame = 0;
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
        _sprite.setSourceRectangle(make_shared<Rectangle>(currentFrameData.sheetX, currentFrameData.sheetY, frameDimensions.first, frameDimensions.second));
        _currentFrameTimer = currentFrameData.displayTime;
    }

}
