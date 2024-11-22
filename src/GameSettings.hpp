#ifndef GAME_SETTINGS_HPP
#define GAME_SETTINGS_HPP

#include <string>
using namespace std;

class GameSettings
{
public:
    // used to find a safe location to write data like save files and logs
    static constexpr char *ORGANIZATION_NAME = "LeoDefaultOrg";
    static constexpr char *APPLICATION_NAME = "LeoDefaultApp";

    static constexpr char *DEFAULT_WINDOW_TITLE = "Test Window";

    static constexpr int DEFAULT_WINDOW_WIDTH = 800;
    static constexpr int DEFAULT_WINDOW_HEIGHT = 800;

    static constexpr int DEFAULT_RENDER_WIDTH = 128;
    static constexpr int DEFAULT_RENDER_HEIGHT = 128;

    static constexpr int TARGET_UPS = 60;

private:
    GameSettings() = default;
    ~GameSettings() = default;
};

#endif

