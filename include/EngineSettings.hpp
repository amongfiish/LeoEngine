#ifndef ENGINE_SETTINGS_HPP
#define ENGINE_SETTINGS_HPP

#include <string>
using namespace std;

class EngineSettings
{
public:
    string organizationName = "LeoEngineDefaultOrg";
    string applicationName = "LeoEngineDefaultApp";
    string defaultWindowTitle = "Leo Engine Project";

    int defaultWindowWidth = 800;
    int defaultWindowHeight = 600;

    int defaultRenderWidth = 800;
    int defaultRenderHeight = 600;

    bool defaultFullscreen = false;
    bool defaultBordered = true;
    bool defaultResizable = false;
};

#endif

