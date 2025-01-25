#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <memory>
#include <unordered_map>
#include <string>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace LeoEngine
{

    class Logger
    {
    public:
        Logger();
        ~Logger();

        static void setOrgAndAppName(std::string organizationName, std::string applicationName);

        void trace(std::string id, std::string content);
        void debug(std::string id, std::string content);
        void info(std::string id, std::string content);
        void warn(std::string id, std::string content);
        void error(std::string id, std::string content);
        void critical(std::string id, std::string content);

        void flush();

    private:
        std::shared_ptr<spdlog::logger> getLogger(std::string id);

        std::unordered_map<std::string, std::shared_ptr<spdlog::logger>> _spdLoggers;

        static std::string _organizationName;
        static std::string _applicationName;
    };

}

#endif
