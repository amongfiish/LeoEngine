#ifndef GAME_HPP
#define GAME_HPP

#include "LeoEngine/SceneCollection.hpp"

namespace LeoEngine
{

    class Game
    {
    public:
        Game()
        {
            
        }

        ~Game()
        {
            
        }

        void update(double deltaTime)
        {
            _scenes.update(deltaTime);
        }

        void draw()
        {
            _scenes.draw();
        }

        SceneCollection &getSceneCollection()
        {
            return _scenes;
        }

    private:
        SceneCollection _scenes;
    };

}

#endif

