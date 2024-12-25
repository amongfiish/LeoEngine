#include <stdexcept>
#include <string>
#include "LeoEngine/Audio.hpp"

namespace LeoEngine
{

    Audio::Audio()
        : _musicLoader("music"),
        _soundEffectLoader("sfx")
    {
        if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
        {
            throw runtime_error("Couldn't initialize SDL audio.");
        }

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            throw runtime_error("Couldn't start SDL mixer.");
        }
    }

    Audio::~Audio()
    {
        Mix_CloseAudio();
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
    }

    void Audio::playMusic(string filename, int loops, int fadeInMilliseconds, double startPosition)
    {
        Mix_FadeInMusicPos(_musicLoader.get(filename).getSDLMusicObject(), loops, fadeInMilliseconds, startPosition);
    }

    void Audio::pauseMusic()
    {
        Mix_PauseMusic();
    }

    void Audio::resumeMusic()
    {
        Mix_ResumeMusic();
    }

    void Audio::restartMusic()
    {
        Mix_RewindMusic();
    }

    void Audio::stopMusic(int fadeOutMilliseconds)
    {
        if (fadeOutMilliseconds <= 0)
        {
            Mix_HaltMusic();
        }
        else
        {
            Mix_FadeOutMusic(fadeOutMilliseconds);
        }
    }

    void Audio::setMusicVolume(double volume)
    {
        Mix_VolumeMusic(static_cast<int>(MIX_MAX_VOLUME * volume));
    }

    void Audio::setMusicPosition(double position)
    {
        Mix_SetMusicPosition(position);
    }

    void Audio::playSoundEffect(string filename, int loops)
    {
        Mix_PlayChannel(-1, _soundEffectLoader.get(filename).getSDLChunkObject(), loops);
    }

    void Audio::setSoundEffectVolume(string filename, double volume)
    {
        Mix_VolumeChunk(_soundEffectLoader.get(filename).getSDLChunkObject(), static_cast<int>(MIX_MAX_VOLUME * volume));
    }

}
