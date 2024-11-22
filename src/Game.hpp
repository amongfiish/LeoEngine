#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "Scene.hpp"
using namespace std;

class Game
{
public:
    Game()
    {

    }

    ~Game()
    {

    }

    void update()
    {
        if (_currentScene == nullptr)
        {
            return;
        }

        _currentScene->update();
    }

    void draw()
    {
        if (_currentScene == nullptr)
        {
            return;
        }

        _currentScene->draw();
    }

    template<class T>
    int addScene()
    {
        T *newScene = new T;
        _scenes.push_back(dynamic_cast<Scene *>(newScene));

        int newSceneID = static_cast<int>(_scenes.size() - 1);
        return newSceneID;
    }

    void setCurrentScene(int scene)
    {
        _currentScene = _scenes.at(scene);
    }

private:
    vector<Scene *> _scenes;
    Scene *_currentScene = nullptr;
};

#endif

