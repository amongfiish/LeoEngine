#ifndef SOUND_HPP
#define SOUND_HPP

#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3/SDL.h>

namespace LeoEngine
{

    class Sound
    {
    public:
        Sound(std::string filepath, bool decompress);
        ~Sound();

        MIX_Audio *getMixAudioObject();

    private:
        MIX_Audio *_audio;
    };

    class CompressedSound : public Sound
    {
    public:
        CompressedSound(std::string filepath);
    };

    class UncompressedSound : public Sound
    {
    public:
        UncompressedSound(std::string filepath);
    };

}

#endif

