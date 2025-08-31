#include <stdexcept>

#include "LeoEngine/Saver.hpp"

namespace LeoEngine
{

    std::string Saver::_organizationName = "LeoEngineDefaultOrg";
    std::string Saver::_applicationName = "LeoEngineDefaultApp";

    Saver::Saver(std::string filename)
    {
        std::string path = SDL_GetPrefPath(_organizationName.c_str(), _applicationName.c_str());
        path += filename;

        _file.open(path.c_str());
        if (!_file.good())
        {
            _file.open(path.c_str(), std::fstream::in | std::fstream::out | std::fstream::trunc);

            if (!_file.good())
            {
                throw std::runtime_error("Saver failed to open file.");
            }
        }
    }

    Saver::~Saver()
    {
        _file.close();
    }

    void Saver::moveTo(int position)
    {
        _file.seekp(static_cast<std::streampos>(position));
        _file.seekg(static_cast<std::streampos>(position));
    }

    void Saver::setOrgAndAppName(std::string organizationName, std::string applicationName)
    {
        _organizationName = organizationName;
        _applicationName = applicationName;
    }

    std::string Saver::getLine()
    {
        _file.getline(_buffer, BUFFER_SIZE);

        return std::string(_buffer);
    }

    std::string Saver::getCharacters(int numberOfCharacters)
    {
        if (numberOfCharacters >= BUFFER_SIZE)
        {
            numberOfCharacters = BUFFER_SIZE - 1;
        }

        _file.get(_buffer, numberOfCharacters);

        return std::string(_buffer);
    }

    void Saver::writeCharacters(std::string characters)
    {
        _file.write(characters.c_str(), characters.size());
    }

}
