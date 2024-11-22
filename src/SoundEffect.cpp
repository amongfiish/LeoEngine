#include <stdexcept>
#include "SoundEffect.hpp"

SoundEffect::SoundEffect(string filepath)
{
    Mix_Chunk *newChunk = Mix_LoadWAV(filepath.c_str());
    if (newChunk == nullptr)
    {
        throw runtime_error("Couldn't load new sdl chunk.");   
    }

    _chunk = newChunk;
}

SoundEffect::~SoundEffect()
{
    Mix_FreeChunk(_chunk);
}

Mix_Chunk *SoundEffect::getSDLChunkObject()
{
    return _chunk;
}

