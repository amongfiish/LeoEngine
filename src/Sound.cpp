#include <stdexcept>

#include "LeoEngine/Sound.hpp"
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Logger.hpp"

namespace LeoEngine
{

    Sound::Sound(std::string filepath, bool decompress)
    {
        _audio = MIX_LoadAudio(NULL, filepath.c_str(), decompress);
        if (_audio == NULL)
        {
            std::string errorString = "Failed to load new MIX_Audio from path '" + filepath + "'. MIX_GetError output: '" + SDL_GetError() + "'";
            Services::get().getLogger()->critical("Sound", errorString);
            Services::get().getLogger()->flush();
            
            throw std::runtime_error(errorString);
        }
    }

    Sound::~Sound()
    {
        MIX_DestroyAudio(_audio);
    }

    MIX_Audio *Sound::getMixAudioObject()
    {
        return _audio;
    }

    CompressedSound::CompressedSound(std::string filepath)
        : Sound(filepath, false)
    {}

    UncompressedSound::UncompressedSound(std::string filepath)
        : Sound(filepath, true)
    {}

}

