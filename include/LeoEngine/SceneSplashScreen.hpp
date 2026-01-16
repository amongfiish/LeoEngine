#ifndef SCENE_SPLASH_SCREEN
#define SCENE_SPLASH_SCREEN

#include <memory>
#include <string>
#include "LeoEngine/Scene.hpp"
#include "LeoEngine/Animation.hpp"
#include "LeoEngine/Rectangle.hpp"
#include "LeoEngine/SpriteAnimated.hpp"
#include "LeoEngine/Colour.hpp"

namespace LeoEngine
{

    class SceneSplashScreen : public Scene
    {
    public:
        SceneSplashScreen();
        virtual ~SceneSplashScreen();

        virtual void onActivate() override;
        virtual void onDeactivate() override;

        virtual void update(double deltaTime) override;
        virtual void draw() override;

        void setSplash(std::shared_ptr<Animation> animation, std::shared_ptr<Rectangle<int>> position, double duration, Colour backgroundColour, std::string soundEffectFilename);

        void setNextSceneID(int id);

        void setFadeDuration(double fadeDuration);

    private:
        SpriteAnimated _animatedSprite;
        Colour _backgroundColour;
        std::string _soundEffectFilename;

        double _duration;
        double _remainingDuration;
        bool _endEventSent;

        int _nextSceneID;

        double _fadeDuration;
    };

}

#endif

