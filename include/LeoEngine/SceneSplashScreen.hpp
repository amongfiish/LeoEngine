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

        virtual void onActivate();
        virtual void onDeactivate();

        virtual void update();
        virtual void draw();

        void setSplash(std::shared_ptr<Animation> animation, std::shared_ptr<Rectangle<int>> position, int duration, Colour backgroundColour, std::string soundEffectFilename);

        void setNextSceneID(int id);

    private:
        SpriteAnimated _animatedSprite;
        Colour _backgroundColour;
        std::string _soundEffectFilename;

        int _duration;
        int _remainingFrames;
        bool _endEventSent;

        int _nextSceneID;
    };

    }

#endif

