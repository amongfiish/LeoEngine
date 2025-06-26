#ifndef ENGINE_SETTINGS_HPP
#define ENGINE_SETTINGS_HPP

#include <string>

namespace LeoEngine
{

    class EngineSettings
    {
    public:
        std::string organizationName = "LeoEngineDefaultOrg";
        std::string applicationName = "LeoEngineDefaultApp";
        std::string defaultWindowTitle = "Leo Engine Project";

        int defaultWindowWidth = 800;
        int defaultWindowHeight = 600;

        int defaultRenderWidth = 800;
        int defaultRenderHeight = 600;

        bool defaultFullscreen = false;
        bool defaultBordered = true;
        bool defaultResizable = false;

        int framerate = 60;
    };

}

#endif

