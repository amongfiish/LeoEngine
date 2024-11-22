#include <stdexcept>
#include "Music.hpp"

Music::Music(string filepath)
{
    Mix_Music *newMusic = Mix_LoadMUS(filepath.c_str());
    if (newMusic == nullptr)
    {
        throw runtime_error("Couldn't load music object.");
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

