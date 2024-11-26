#include "Saver.hpp"

string Saver::_organizationName = "LeoEngineDefaultOrg";
string Saver::_applicationName = "LeoEngineDefaultApp";

Saver::Saver(string filename)
{
    string path = SDL_GetPrefPath(_organizationName.c_str(), _applicationName.c_str());
    path += filename;

    _file.open(path.c_str());
}

Saver::~Saver()
{
    _file.close();
}

void Saver::moveTo(int position)
{
    _file.seekp(static_cast<streampos>(position));
    _file.seekg(static_cast<streampos>(position));
}

void Saver::setOrgAndAppName(string organizationName, string applicationName)
{
    _organizationName = organizationName;
    _applicationName = applicationName;
}

string Saver::getLine()
{
    _file.getline(_buffer, BUFFER_SIZE);

    return string(_buffer);
}

string Saver::getCharacters(int numberOfCharacters)
{
    if (numberOfCharacters >= BUFFER_SIZE)
    {
        numberOfCharacters = BUFFER_SIZE - 1;
    }

    _file.get(_buffer, numberOfCharacters);

    return string(_buffer);
}

void Saver::writeCharacters(string characters)
{
    _file.write(characters.c_str(), characters.size());
}

