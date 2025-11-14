#ifndef AUDIO_HPP
#define AUDIO_HPP

#if defined(__linux__) || defined(__APPLE__)
    #include <SDL3/SDL.h>
    #include <SDL3_mixer/SDL_mixer.h>
#elif defined(_WIN32)
    #include <SDL.h>
    #include <SDL_mixer.h>
#endif

#include <array>
#include <string>
#include <map>
#include "LeoEngine/Sound.hpp"
#include "LeoEngine/Loader.hpp"
#include "LeoEngine/RandomNumberGenerator.hpp"

namespace LeoEngine
{

    class Audio
    {
    public:
        Audio();
        ~Audio();

        Sound *getSound(std::string filename, bool decompress);

        // play an uncompressed sound one time.
        // does not give a reference or any ability to modify after firing.
        void playOneShot(std::string filename);
        void playOneShot(Sound *sound);

        int createTrack();

        void setTrackSound(int trackId, Sound *sound);

        void addTrackTag(int trackId, std::string tag);
        void removeTrackTag(int trackId, std::string tag);

        void playTrack(int trackId, int loops=0, double fadeInSeconds=0);
        void playTag(std::string tag, int loops=0, double fadeInSeconds=0);

        void stopTrack(int trackId, int fadeOutSeconds=0);
        void stopTag(std::string tag, int fadeOutSeconds=0);

    private:
        MIX_Mixer *_mixer;

        std::map<int, MIX_Track *> _tracks;
        unsigned int _nextTrackId;

        Loader<CompressedSound> _musicLoader;
        Loader<UncompressedSound> _soundEffectLoader;
    };

}

#endif

