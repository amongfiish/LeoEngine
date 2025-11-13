#ifndef FILE_HPP
#define FILE_HPP

#if defined(__linux__) || defined(__APPLE__)
    #include <SDL3/SDL.h>
#elif defined(_WIN32)
    #include <SDL.h>
#endif

#include <string>

namespace LeoEngine
{

    enum class FileSeekOrigin
    {
        START,  // start of file
        CURSOR, // current seek 'cursor' location
        END     // end of file
    };


    class File
    {
    public:
        // engine related
        static void setWriteDirectory(std::string organizationDirectoryName, std::string applicationDirectoryName); // used to be Logger::setOrgAndAppName

        // utility functions
        static const char getPathSeparator();
        static const std::string getApplicationDataDirectory();
        static const std::string getWriteDirectory();

        File(std::string filepath, bool isBinary);
        ~File();
    
        // opens the file for reading and writing
        void create();  // will destroy an existing file
        void open();    // throws an exception if the file doesn't exist

        void close();

        bool exists() const;
        bool isOpen() const;

        // distance is in bytes; can be negative
        void seek(FileSeekOrigin origin, int numberOfBytes);
        
        std::string read(int numberOfBytes);

        void write(std::string data);

    private:
        static std::string _writeDirectory;

        std::string _filepath;
        bool _isBinary;

        SDL_IOStream *_sdlFile;

        bool _isOpen;
    };

}

#endif

