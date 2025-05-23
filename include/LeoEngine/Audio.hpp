#ifndef AUDIO_HPP
#define AUDIO_HPP

#if defined(__linux__) || defined(__APPLE__)
    #include <SDL2/SDL.h>
    #include <SDL_mixer.h>
#elif defined(_WIN32)
    #include <SDL.h>
    #include <SDL_mixer.h>
#endif

#include <string>
#include "LeoEngine/Music.hpp"
#include "LeoEngine/SoundEffect.hpp"
#include "LeoEngine/Loader.hpp"

namespace LeoEngine
{

    class Audio
    {
    public:
        Audio();
        ~Audio();

        // start position is in seconds. loops=0 means the song will play once. -1 means forever.
        void playMusic(std::string filename, int loops = 0, int fadeInMilliseconds = 0, double startPosition = 0);
        void pauseMusic();
        void resumeMusic();
        void restartMusic();
        void stopMusic(int fadeOutMilliseconds);

        // volume is a double between 0 (muted) and 1 (full volume).
        void setMusicVolume(double volume);

        // see playMusic declaration above for position description
        void setMusicPosition(double position);

        void playSoundEffect(std::string filename, int loops = 0);
        void stopAllSoundEffects();
        void setSoundEffectVolume(std::string filename, double volume);

    private:
        Loader<Music> _musicLoader;
        Loader<SoundEffect> _soundEffectLoader;
    };

}

#endif

