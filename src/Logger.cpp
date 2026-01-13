#include <SDL3/SDL.h>

#include "LeoEngine/Logger.hpp"
#include "LeoEngine/File.hpp"

namespace LeoEngine
{

    Logger::Logger()
    {
        spdlog::set_level(spdlog::level::trace);
    }

    Logger::~Logger()
    {

    }

    void Logger::trace(std::string id, std::string content)
    {
        auto logger = getLogger(id);
        logger->trace(content);
        spdlog::trace(content);
    }

    void Logger::debug(std::string id, std::string content)
    {
        auto logger = getLogger(id);
        logger->debug(content);
        spdlog::debug(content);
    }

    void Logger::info(std::string id, std::string content)
    {
        auto logger = getLogger(id);
        logger->info(content);
        spdlog::info(content);
    }

    void Logger::warn(std::string id, std::string content)
    {
        auto logger = getLogger(id);
        logger->warn(content);
        spdlog::warn(content);
    }

    void Logger::error(std::string id, std::string content)
    {
        auto logger = getLogger(id);
        logger->error(content);
        spdlog::error(content);
    }

    void Logger::critical(std::string id, std::string content)
    {
        auto logger = getLogger(id);
        logger->critical(content);
        spdlog::critical(content);
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

            std::shared_ptr<spdlog::logger> logger = nullptr;

            try
            {
                 logger = spdlog::basic_logger_mt(id, path);
            }
            catch (const spdlog::spdlog_ex &ex)
            {
                std::string errorMessage = std::string("Failed to create logger. Error: ") + ex.what();
                spdlog::error(errorMessage);
                throw std::runtime_error(errorMessage);
            }

            return _spdLoggers.insert(make_pair(id, logger)).first->second;
        }

        return logger->second;
    }

}
