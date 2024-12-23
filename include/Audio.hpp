#ifndef AUDIO_HPP
#define AUDIO_HPP

#if defined(__linux__) || defined(__APPLE__)
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_mixer.h>
#elif defined(_WIN32)
    #include <SDL.h>
    #include <SDL_mixer.h>
#endif

#include <string>
#include "Music.hpp"
#include "SoundEffect.hpp"
#include "Loader.hpp"
using namespace std;

class Audio
{
public:
    Audio();
    ~Audio();

    // start position is in seconds. loops=1 means the song will play once. -1 means forever.
    void playMusic(string filename, int loops=1, int fadeInMilliseconds=0, double startPosition=0);
    void pauseMusic();
    void resumeMusic();
    void restartMusic();
    void stopMusic(int fadeOutMilliseconds);

    // volume is a double between 0 (muted) and 1 (full volume).
    void setMusicVolume(double volume);
    
    // see playMusic declaration above for position description
    void setMusicPosition(double position);

    void playSoundEffect(string filename, int loops=1);
    void setSoundEffectVolume(string filename, double volume);

private:
    Loader<Music> _musicLoader;
    Loader<SoundEffect> _soundEffectLoader;
};

#endif

