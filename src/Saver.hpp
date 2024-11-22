#ifndef SAVER_HPP
#define SAVER_HPP

#if defined(__linux__) || defined(__APPLE__)
    #include <SDL2/SDL.h>
#elif defined(_WIN32)
    #include <SDL.h>
#endif

#include <string>
#include <fstream>
using namespace std;

#ifdef _WIN32
    #define PATH_SEPARATOR '\\'
#else
    #define PATH_SEPARATOR '/'
#endif

class Saver
{
public:
    Saver(string filename);
    ~Saver();

    // scan around the file
    void moveTo(int position);

    // read and write characters from the file
    // NOTE: read operations only work up to 100 characters.
    //       If more are needed increase BUFFER_SIZE.
    string getLine();
    string getCharacters(int numberOfCharacters);
    void writeCharacters(string characters);

private:
    fstream _file;

    static constexpr int BUFFER_SIZE = 100;
    char _buffer[BUFFER_SIZE];
};

#endif

