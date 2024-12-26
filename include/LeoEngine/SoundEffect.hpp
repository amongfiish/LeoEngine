#ifndef SOUND_EFFECT_HPP
#define SOUND_EFFECT_HPP

#if defined(__linux__) || defined(__APPLE__)
    #include <SDL_mixer.h>
#elif defined(_WIN32)
    #include <SDL_mixer.h>
#endif

#include <string>
using namespace std;

namespace LeoEngine
{

    class SoundEffect
    {
    public:
        SoundEffect(string filepath);
        ~SoundEffect();

        Mix_Chunk *getSDLChunkObject();

    private:
        Mix_Chunk *_chunk = nullptr;
    };

}

#endif

