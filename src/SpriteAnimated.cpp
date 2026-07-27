#include <stdexcept>
#include "LeoEngine/SpriteAnimated.hpp"
#include "LeoEngine/Rectangle.hpp"
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Logger.hpp"

namespace LeoEngine
{

    SpriteAnimated::SpriteAnimated()
        : _animation(nullptr),
          _loop(true),
          _reverse(false),
          _paused(false),
          _startFrame(0),
          _currentFrame(0),
          _currentFrameTimer(0)
    {

    }

    SpriteAnimated::~SpriteAnimated()
    {

    }

    void SpriteAnimated::update(double deltaTime)
    {
        if (_animation == nullptr || _paused)
        {
            return;
        }

        if (_currentFrameTimer > 0)
        {
            _currentFrameTimer -= deltaTime;
            return;
        }

        while (_currentFrameTimer <= 0)
        {
            if (_reverse)
            {
                _currentFrame -= 1;
                if (_currentFrame < 0)
                {
                    _currentFrame += _animation->getNumberOfFrames();
                }
            }
            else
            {
                _currentFrame = (_currentFrame + 1) % _animation->getNumberOfFrames();
            }
            
            if (!_loop && _currentFrame == _startFrame)
            {
                pauseAnimation();
                break;
            }

            double resultingFrameTimer = _currentFrameTimer;
            fetchFrameData();
            _currentFrameTimer += resultingFrameTimer;
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
        int numberOfFrames = _animation->getNumberOfFrames();
        if (frame < 0)
        {
            frame += numberOfFrames;
        }

        if (frame > numberOfFrames - 1 || frame < 0)
        {
            std::string errorMessage =
                "Provided frame (" + std::to_string(frame) +
                ") outside acceptable range [" +
                std::to_string(-numberOfFrames) + ", " +
                std::to_string(numberOfFrames - 1) + "].";
            LeoEngine::Services::get().getLogger()->error(
                "SpriteAnimated",
                errorMessage);
            throw std::runtime_error(errorMessage);
        }

        _currentFrame = frame;
        _startFrame = frame;
        fetchFrameData();
    }

    void SpriteAnimated::setLoop(bool shouldLoop)
    {
        _loop = shouldLoop;
    }

    void SpriteAnimated::setReverse(bool reverse)
    {
        _reverse = reverse;
    }

    SpriteStatic &SpriteAnimated::getSprite()
    {
        return _sprite;
    }

    bool SpriteAnimated::isPaused() const
    {
        return _paused;
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
