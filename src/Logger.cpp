#if defined(__linux__) || defined(__APPLE__)
    #include <SDL2/SDL.h>
#elif defined(_WIN32)
    #include <SDL.h>
#endif

#include "Logger.hpp"

string Logger::_organizationName = "LeoEngineDefaultOrg";
string Logger::_applicationName = "LeoEngineDefaultApp";

Logger::Logger()
{

}

Logger::~Logger()
{

}

void Logger::setOrgAndAppName(string organizationName, string applicationName)
{
    _organizationName = organizationName;
    _applicationName = applicationName;
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

void Logger::flush()
{
    for (auto logger : _spdLoggers) 
    {
        logger.second->flush();
    }
}

shared_ptr<spdlog::logger> Logger::getLogger(string id)
{
    // create a logger with this ID, if one doesn't already exist
    auto logger = _spdLoggers.find(id);
    if (logger == _spdLoggers.end())
    {
        string path = SDL_GetPrefPath(_organizationName.c_str(), _applicationName.c_str());
        path += "log.txt";
        return _spdLoggers.insert(make_pair(id, spdlog::basic_logger_mt(id, path))).first->second;
    }

    return logger->second;
}

