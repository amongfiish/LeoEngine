#include "Saver.hpp"
#include "GameSettings.hpp"

Saver::Saver(string filename)
{
    string path = SDL_GetPrefPath(GameSettings::ORGANIZATION_NAME, GameSettings::APPLICATION_NAME);
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

