#if defined(__linux__) || defined(__APPLE__)
    #include <SDL3/SDL.h>
#elif defined(_WIN32)
    #include <SDL.h>
#endif

#include "LeoEngine/Logger.hpp"
#include "LeoEngine/File.hpp"

namespace LeoEngine
{

    Logger::Logger()
    {

    }

    Logger::~Logger()
    {

    }

    void Logger::trace(std::string id, std::string content)
    {
        auto logger = getLogger(id);
        logger->trace(content);
    }

    void Logger::debug(std::string id, std::string content)
    {
        auto logger = getLogger(id);
        logger->debug(content);
    }

    void Logger::info(std::string id, std::string content)
    {
        auto logger = getLogger(id);
        logger->info(content);
    }

    void Logger::warn(std::string id, std::string content)
    {
        auto logger = getLogger(id);
        logger->warn(content);
    }

    void Logger::error(std::string id, std::string content)
    {
        auto logger = getLogger(id);
        logger->error(content);
    }

    void Logger::critical(std::string id, std::string content)
    {
        auto logger = getLogger(id);
        logger->critical(content);
    }

    std::string Logger::getSDLError()
    {
        return SDL_GetError();
    }

    void Logger::flush()
    {
        for (auto logger : _spdLoggers) 
        {
            logger.second->flush();
        }
    }

    std::shared_ptr<spdlog::logger> Logger::getLogger(std::string id)
    {
        // create a logger with this ID, if one doesn't already exist
        auto logger = _spdLoggers.find(id);
        if (logger == _spdLoggers.end())
        {
            std::string path = File::getWriteDirectory();
            path += "log.txt";
            return _spdLoggers.insert(make_pair(id, spdlog::basic_logger_mt(id, path))).first->second;
        }

        return logger->second;
    }

}
