#include <stdexcept>
#include "LeoEngine/Music.hpp"

namespace LeoEngine
{

    Music::Music(std::string filepath)
    {
        Mix_Music *newMusic = Mix_LoadMUS(filepath.c_str());
        if (newMusic == nullptr)
        {
            throw std::runtime_error("Couldn't load music object.");
        }

        _music = newMusic;
    }

    Music::~Music()
    {
        Mix_FreeMusic(_music);
    }

    Mix_Music *Music::getSDLMusicObject()
    {
        return _music;
    }

}
