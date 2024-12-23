#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <memory>
#include <unordered_map>
#include <string>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
using namespace std;

class Logger
{
public:
    Logger();
    ~Logger();

    static void setOrgAndAppName(string organizationName, string applicationName);

    void trace(string id, string content);
    void debug(string id, string content);
    void info(string id, string content);
    void warn(string id, string content);
    void error(string id, string content);
    void critical(string id, string content);

    void flush();

private:
    shared_ptr<spdlog::logger> getLogger(string id);

    unordered_map<string, shared_ptr<spdlog::logger>> _spdLoggers;

    static string _organizationName;
    static string _applicationName;
};

#endif

