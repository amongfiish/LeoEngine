#include <stdexcept>
#include <string>
#include "LeoEngine/Audio.hpp"
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Logger.hpp"

namespace LeoEngine
{

    Audio::Audio()
        : _musicLoader("music"),
          _soundEffectLoader("sfx")
    {
        if (!SDL_InitSubSystem(SDL_INIT_AUDIO))
        {
            throw std::runtime_error(std::string("Couldn't initialize SDL audio. SDL_GetError output: ") + SDL_GetError());
        }

        if (!MIX_Init())
        {
            throw std::runtime_error(std::string("Couldn't start SDL mixer. SDL_GetError output: ") + SDL_GetError());
        }

        _mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
        if (_mixer == NULL)
        {
            throw std::runtime_error(std::string("Couldn't create new MIX_Mixer. SDL_GetError output: ") + SDL_GetError());
        }
    }

    Audio::~Audio()
    {
        MIX_Quit();
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
    }

    Sound *Audio::getSound(std::string filename, bool decompress)
    {
        if (decompress)
        {
            return dynamic_cast<Sound *>(&_soundEffectLoader.get(filename));
        }
        else
        {
            return dynamic_cast<Sound *>(&_musicLoader.get(filename));
        }
    }

    void Audio::playOneShot(std::string filename)
    {
        Sound *oneShotSound = getSound(filename, true);
        if (oneShotSound == NULL)
        {
            std::string errorString = std::string("Invalid filename provided to playOneShot: '") + filename + "'.";
            Services::get().getLogger()->error("Audio", errorString);
            throw std::runtime_error(errorString);
        }

        MIX_PlayAudio(_mixer, oneShotSound->getMixAudioObject());
    }

    void Audio::playOneShot(Sound *sound)
    {
        if (sound == nullptr)
        {
            std::string errorString = "Null pointer provided to playOneShot.";
            Services::get().getLogger()->error("Audio", errorString);
            throw std::runtime_error(errorString);
        }

        MIX_PlayAudio(_mixer, sound->getMixAudioObject());
    }

    int Audio::createTrack()
    {
        MIX_Track *newTrack = MIX_CreateTrack(_mixer);
        if (newTrack == NULL)
        {
            std::string errorString = std::string("Couldn't create new MIX_Track. SDL_GetError output: ") + SDL_GetError();
            Services::get().getLogger()->error("Audio", errorString);
            throw std::runtime_error(errorString);
        }

        _tracks.insert(std::make_pair(_nextTrackId, newTrack));
        return _nextTrackId++;
    }

    void Audio::setTrackSound(int trackId, Sound *sound)
    {
        if (sound == nullptr)
        {
            std::string errorString = "Attempting to assign nullptr Sound to track.";
            Services::get().getLogger()->error("Audio", errorString);
            throw std::runtime_error(errorString);
        }

        auto trackIt = _tracks.find(trackId);
        if (trackIt == _tracks.end())
        {
            std::string errorString = "Attempting to set sound of non-existent track.";
            Services::get().getLogger()->error("Audio", errorString);
            throw std::runtime_error(errorString);
        }

        MIX_SetTrackAudio(trackIt->second, sound->getMixAudioObject());
    }

    void Audio::addTrackTag(int trackId, std::string tag)
    {
        auto trackIt = _tracks.find(trackId);
        if (trackIt == _tracks.end())
        {
            std::string errorString = "Attempting to set tag of non-existent track.";
            Services::get().getLogger()->error("Audio", errorString);
            throw std::runtime_error(errorString);
        }

        MIX_TagTrack(trackIt->second, tag.c_str());
    }

    void Audio::removeTrackTag(int trackId, std::string tag)
    {
        auto trackIt = _tracks.find(trackId);
        if (trackIt == _tracks.end())
        {
            std::string errorString = "Attempting to unset tag of non-existent track.";
            Services::get().getLogger()->error("Audio", errorString);
            throw std::runtime_error(errorString);
        }

        MIX_UntagTrack(trackIt->second, tag.c_str());
    }

    SDL_PropertiesID createNewAudioProperties(int loops, double fadeInSeconds)
    {
        SDL_PropertiesID newProperties = SDL_CreateProperties();

        SDL_SetNumberProperty(newProperties, MIX_PROP_PLAY_LOOPS_NUMBER, loops);
        SDL_SetNumberProperty(newProperties, MIX_PROP_PLAY_FADE_IN_FRAMES_NUMBER, static_cast<int>(fadeInSeconds * 1000));

        return newProperties;
    }

    void Audio::playTrack(int trackId, int loops, double fadeInSeconds)
    {
        SDL_PropertiesID newProperties = createNewAudioProperties(loops, fadeInSeconds);

        auto trackIt = _tracks.find(trackId);
        if (trackIt == _tracks.end())
        {
            std::string errorString = "Attempting to set tag of non-existent track.";
            Services::get().getLogger()->error("Audio", errorString);
            throw std::runtime_error(errorString);
        }

        MIX_PlayTrack(trackIt->second, newProperties);

        SDL_DestroyProperties(newProperties);
    }

    void Audio::playTag(std::string tag, int loops, double fadeInSeconds)
    {
        SDL_PropertiesID newProperties = createNewAudioProperties(loops, fadeInSeconds);

        bool success = MIX_PlayTag(_mixer, tag.c_str(), newProperties);

        SDL_DestroyProperties(newProperties);

        if (!success)
        {
            std::string errorString = std::string("Unable to play tag '") + tag + "'. SDL_GetError output: '" + SDL_GetError() + "'.";
            Services::get().getLogger()->error("Audio", errorString);
            throw std::runtime_error(errorString);
        }

    }

    void Audio::stopTrack(int trackId, int fadeOutSeconds)
    {
        auto trackIt = _tracks.find(trackId);
        if (trackIt == _tracks.end())
        {
            std::string errorString = "Attempting to set tag of non-existent track.";
            Services::get().getLogger()->error("Audio", errorString);
            throw std::runtime_error(errorString);
        }

        // why are there still silly inconsistencies like this in the SDL library?
        int fadeOutFrames = MIX_TrackMSToFrames(trackIt->second, static_cast<int>(fadeOutSeconds * 1000));
        MIX_StopTrack(trackIt->second, fadeOutFrames);
    }

    void Audio::stopTag(std::string tag, int fadeOutSeconds)
    {
        bool success = MIX_StopTag(_mixer, tag.c_str(), static_cast<int>(fadeOutSeconds * 1000));

        if (!success)
        {
            std::string errorString = std::string("Unable to stop tag '") + tag + "'. SDL_GetError output: '" + SDL_GetError() + "'.";
            Services::get().getLogger()->error("Audio", errorString);
            throw std::runtime_error(errorString);
        }
    }

}

