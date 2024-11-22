#if defined(__linux__) || defined(__APPLE__)
    #include <SDL2/SDL.h>
#elif defined(_WIN32)
    #include <SDL.h>
#endif

#include "Logger.hpp"
#include "GameSettings.hpp"

Logger::Logger()
{

}

Logger::~Logger()
{

}

void Logger::trace(string id, string content)
{
    auto logger = getLogger(id);
    logger->trace(content);
}

void Logger::debug(string id, string content)
{
    auto logger = getLogger(id);
    logger->debug(content);
}

void Logger::info(string id, string content)
{
    auto logger = getLogger(id);
    logger->info(content);
}

void Logger::warn(string id, string content)
{
    auto logger = getLogger(id);
    logger->warn(content);
}

void Logger::error(string id, string content)
{
    auto logger = getLogger(id);
    logger->error(content);
}

void Logger::critical(string id, string content)
{
    auto logger = getLogger(id);
    logger->critical(content);
}

shared_ptr<spdlog::logger> Logger::getLogger(string id)
{
    // create a logger with this ID, if one doesn't already exist
    auto logger = _spdLoggers.find(id);
    if (logger == _spdLoggers.end())
    {
        string path = SDL_GetPrefPath(GameSettings::ORGANIZATION_NAME, GameSettings::APPLICATION_NAME);
        path += "log.txt";
        return _spdLoggers.insert(make_pair(id, spdlog::basic_logger_mt(id, path))).first->second;
    }

    return logger->second;
}

