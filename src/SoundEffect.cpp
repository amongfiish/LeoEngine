#include <stdexcept>
#include "LeoEngine/SoundEffect.hpp"
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Logger.hpp"

namespace LeoEngine
{

    SoundEffect::SoundEffect(std::string filepath)
    {
        Mix_Chunk *newChunk = Mix_LoadWAV(filepath.c_str());
        if (newChunk == nullptr)
        {
            std::string message = "Couldn't load new sound effect from file at '";
            message = message + filepath + "'. SDL error: '" + Mix_GetError() + "'.";
            Services::get().getLogger()->critical("SoundEffect", message);
            Services::get().getLogger()->flush();
            throw std::runtime_error("Couldn't load new sdl chunk.");
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

}
