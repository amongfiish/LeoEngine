#ifndef SCENE_COLLECTION_HPP
#define SCENE_COLLECTION_HPP

#include <vector>
#include <functional>
#include "LeoEngine/Scene.hpp"
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Input.hpp"
#include "LeoEngine/Events.hpp"
#include "LeoEngine/Logger.hpp"
#include "LeoEngine/Graphics.hpp"
#include "LeoEngine/EventChangeScene.hpp"
#include "LeoEngine/RenderTarget.hpp"

namespace LeoEngine
{

    class SceneCollection
    {
    public:
        SceneCollection()
            : _currentScene(nullptr),
            _nextScene(nullptr),
            _transitionElapsedFrames(0),
            _transitionTotalFrames(0),
            _fadeRenderTarget(100, 100),
            _transitionSecondHalf(false),
            update(std::bind(&SceneCollection::normalUpdate, this)),
            draw(std::bind(&SceneCollection::normalDraw, this))
        {
            Services::get().getEvents()->addCallback(EventType::CHANGE_SCENE, bind(&SceneCollection::sceneChangeCallback, this, placeholders::_1));
            Services::get().getGraphics()->setRenderTarget(&_fadeRenderTarget);

            LeoEngine::Colour black(0, 0, 0, 255);
            Services::get().getGraphics()->fill(black);

            Services::get().getGraphics()->setRenderTarget(nullptr);
        }

        ~SceneCollection()
        {
            for (auto itScene = _scenes.begin(); itScene != _scenes.end(); itScene++)
            {
                if (*itScene != nullptr)
                {
                    delete *itScene;
                    *itScene = nullptr;
                }
            }

            _scenes.clear();
        }

        template<class T>
        int addScene()
        {
            T *newScene = new T;
            _scenes.push_back(dynamic_cast<Scene *>(newScene));

            int newSceneID = static_cast<int>(_scenes.size() - 1);
            return newSceneID;
        }

        // immediate scene change, no effects
        void setCurrentScene(int sceneID)
        {
            if (!sceneIsValid(sceneID))
            {
                return;
            }

            if (_currentScene)
            {
                _currentScene->onDeactivate();
            }

            _currentScene = _scenes.at(sceneID);
            _currentScene->onActivate();
        }

        // fade out (to black), call setCurrentScene, fade in
        void fadeToScene(int sceneID, int transitionFrames)
        {
            if (!sceneIsValid(sceneID))
            {
                return;
            }

            Services::get().getInput()->lockInput();

            _nextScene = _scenes.at(sceneID);

            _transitionElapsedFrames = 0;
            _transitionTotalFrames = transitionFrames;
            _transitionSecondHalf = false;
            update = std::bind(&SceneCollection::fadeUpdate, this);
            draw = std::bind(&SceneCollection::fadeDraw, this);
        }

        std::function<void()> update;
        std::function<void()> draw;

    private:
        bool sceneIsValid(int sceneID)
        {
            Services::get().getLogger()->error("Game", "Provided sceneID is out of range.");

            return sceneID >= 0 && sceneID < _scenes.size();
        }

        bool sceneIsValid(Scene *scene)
        {
            if (scene == nullptr)
            {
                Services::get().getLogger()->error("Game", "Provided nullptr in place of scene.");
                return false;
            }

            for (auto itScene = _scenes.begin(); itScene != _scenes.end(); itScene++)
            {
                if (*itScene == scene)
                {
                    return true;
                }
            }

            Services::get().getLogger()->error("Game", "Provided pointer to invalid scene.");
            return false;
        }

        void setCurrentScene(Scene *scene)
        {
            if (!sceneIsValid(scene))
            {
                return;
            }

            if (_currentScene)
            {
                _currentScene->onDeactivate();
            }

            _currentScene = scene;
            _currentScene->onActivate();
        }

        void normalUpdate()
        {
            if (_currentScene == nullptr)
            {
                return;
            }

            _currentScene->update();
        }

        void normalDraw()
        {
            if (_currentScene == nullptr)
            {
                return;
            }

            _currentScene->draw();
        }

        void fadeUpdate()
        {
            _transitionElapsedFrames++;

            if (!_transitionSecondHalf && _transitionElapsedFrames >= static_cast<double>(_transitionTotalFrames) / 2)
            {
                setCurrentScene(_nextScene);
                _transitionSecondHalf = true;
                _transitionElapsedFrames = 0;
            }
            else if (_transitionElapsedFrames >= static_cast<double>(_transitionTotalFrames) / 2 && _transitionSecondHalf)
            {
                update = std::bind(&SceneCollection::normalUpdate, this);
                draw = std::bind(&SceneCollection::normalDraw, this);

                Services::get().getInput()->unlockInput();
            }

            normalUpdate();
        }

        void fadeDraw()
        {
            normalDraw();

            double opacity;
            if (!_transitionSecondHalf)
            {
                opacity = _transitionElapsedFrames / (_transitionTotalFrames / 2.0);
            }
            else
            {
                opacity = 1 - (_transitionElapsedFrames / (_transitionTotalFrames / 2.0));
            }
            
            Services::get().getGraphics()->copyRenderTarget(_fadeRenderTarget, opacity);
        }

        void sceneChangeCallback(Event *event)
        {
            EventChangeScene *castEvent = dynamic_cast<EventChangeScene *>(event);
            if (!castEvent->fade)
            {
                setCurrentScene(castEvent->sceneID);
            }
            else
            {
                fadeToScene(castEvent->sceneID, 120);
            }
        }

        // scenes
        std::vector<Scene *> _scenes;
        Scene *_currentScene;

        // stuff for transitions
        Scene *_nextScene;
        int _transitionElapsedFrames;
        int _transitionTotalFrames;
        bool _transitionSecondHalf;

        RenderTarget _fadeRenderTarget;
    };

}

#endif
