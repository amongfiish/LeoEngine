#include "LeoEngine/SceneSplashScreen.hpp"
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Graphics.hpp"
#include "LeoEngine/Audio.hpp"
#include "LeoEngine/Events.hpp"
#include "LeoEngine/EventChangeScene.hpp"

namespace LeoEngine
{

    SceneSplashScreen::SceneSplashScreen()
        : _backgroundColour(0x00, 0x00, 0x00, 0xFF),
          _soundEffectFilename(""),
          _duration(0),
          _remainingDuration(0),
          _endEventSent(false),
          _nextSceneID(0),
          _fadeDuration(1.0)
    {

    }

    SceneSplashScreen::~SceneSplashScreen()
    {

    }

    void SceneSplashScreen::onActivate()
    {
        if (_soundEffectFilename != "")
        {
            Services::get().getAudio()->playOneShot(_soundEffectFilename);
        }

        _animatedSprite.setCurrentFrame(0);
        _remainingDuration = _duration;

        _endEventSent = false;

        _animatedSprite.unpauseAnimation();
    }

    void SceneSplashScreen::onDeactivate()
    {

    }

    void SceneSplashScreen::update(double deltaTime)
    {
        if (_remainingDuration <= 0 && !_endEventSent)
        {
            EventChangeScene newEvent(_nextSceneID, true);
            newEvent.fadeDuration = _fadeDuration;

            Event *castEvent = dynamic_cast<Event *>(&newEvent);
            Services::get().getEvents()->broadcast(castEvent);

            _endEventSent = true;
        }

        _animatedSprite.update(deltaTime);

        _remainingDuration -= deltaTime;
    }

    void SceneSplashScreen::draw()
    {
        Services::get().getGraphics()->fill(_backgroundColour);

        _animatedSprite.draw();
    }

    void SceneSplashScreen::setSplash(std::shared_ptr<Animation> animation, std::shared_ptr<Rectangle<int>> position, double duration, Colour backgroundColour, std::string soundEffectFilename)
    {
        _animatedSprite.setAnimation(animation);
        _animatedSprite.setLoop(false);

        _animatedSprite.getSprite().setDestinationRectangle(position);

        _duration = duration;

        _backgroundColour = backgroundColour;

        _soundEffectFilename = soundEffectFilename;
    }

    void SceneSplashScreen::setNextSceneID(int id)
    {
        _nextSceneID = id;
    }

    void SceneSplashScreen::setFadeDuration(double fadeDuration)
    {
        _fadeDuration = fadeDuration;
    }

}

