#ifndef MUSIC_HPP
#define MUSIC_HPP

#if defined(__linux__) || defined(__APPLE__)
    #include <SDL_mixer.h>
#elif defined(_WIN32)
    #include <SDL_mixer.h>
#endif

#include <string>
using namespace std;

namespace LeoEngine
{

    class Music
    {
    public:
        Music(string filepath);
        ~Music();

        Mix_Music *getSDLMusicObject();

    private:
        Mix_Music *_music = nullptr;
    };

}

#endif

