#include <SDL3/SDL.h>
#include <stdexcept>

#include "LeoEngine/File.hpp"
#include "LeoEngine/Services.hpp"
#include "LeoEngine/Logger.hpp"

#if defined(__linux__) || defined(__APPLE__)
    #define PATH_SEPARATOR '/'
#elif defined(_WIN32)
    #define PATH_SEPARATOR '\\'
#endif

namespace LeoEngine
{

    std::string File::_writeDirectory = "";

    void File::setWriteDirectory(std::string organizationDirectoryName, std::string applicationDirectoryName)
    {
        char *prefPath = SDL_GetPrefPath(organizationDirectoryName.c_str(), applicationDirectoryName.c_str());
        _writeDirectory = std::string(prefPath);
        SDL_free(prefPath);
    }

    const char File::getPathSeparator()
    {
        return PATH_SEPARATOR;
    }

    const std::string File::getApplicationDataDirectory()
    {
        return std::string(SDL_GetBasePath());
    }

    const std::string File::getWriteDirectory()
    {
        return _writeDirectory;
    }
    
    File::File(std::string filename, bool isBinary)
        : _isOpen(false)
    {
        if (_writeDirectory.empty())
        {
            char *defaultPrefPath = SDL_GetPrefPath("LeoDefaultOrg", "LeoDefaultApp");
            _writeDirectory = defaultPrefPath;
            SDL_free(defaultPrefPath);
        }

        _filepath = _writeDirectory + filename;
    }

    File::~File()
    {
        if (isOpen())
        {
            close();
        }
    }

    void File::create()
    {
        if (isOpen())
        {
            std::string errorMessage = std::string("Re-creating file '") + _filepath + "', which is already open.";
            Services::get().getLogger()->error("File", errorMessage);
            Services::get().getLogger()->flush();
            throw std::runtime_error(errorMessage);
        }

        _file.open(_filepath.c_str(), std::fstream::in | std::fstream::out | std::fstream::trunc);
        if (_file.fail())
        {
            _isOpen = false;
            std::string errorMessage = "Failed to create file '" + _filepath + "'.";
            Services::get().getLogger()->error("File", errorMessage);
            Services::get().getLogger()->flush();
            throw std::runtime_error(errorMessage);
        }

        _isOpen = true;
    }

    void File::open()
    {
        if (isOpen())
        {
            std::string errorMessage = "Re-opening file '" + _filepath + "', which is already open.";
            Services::get().getLogger()->error("File", errorMessage);
            Services::get().getLogger()->flush();
            throw std::runtime_error(errorMessage);
        }

        _file.open(_filepath.c_str(), std::fstream::in | std::fstream::out);
        if (_file.fail())
        {
            _isOpen = false;
            std::string errorMessage = "Failed to open file '" + _filepath + "'.";
            Services::get().getLogger()->error("File", errorMessage);
            Services::get().getLogger()->flush();
            throw std::runtime_error(errorMessage);
        }

        _isOpen = true;
    }

    void File::close()
    {
        if (!isOpen())
        {
            std::string errorMessage = "Attempting to close file '" + _filepath + "', which isn't open.";
            Services::get().getLogger()->error("File", errorMessage);
            Services::get().getLogger()->flush();
            throw std::runtime_error(errorMessage);
        }

        _file.close();
        _isOpen = false;
    }

    bool File::exists()
    {
        if (isOpen())
        {
            return true;
        }

        _file.open(_filepath.c_str(), std::fstream::in);
        if (_file.fail())
        {
            return false;
        }

        _file.close();

        return true;
    }

    bool File::isOpen() const
    {
        return _isOpen;
    }

    void File::seek(FileSeekOrigin origin, int numberOfBytes)
    {
        int seekResult;

        switch (origin)
        {
        case FileSeekOrigin::START:
            _file.seekp(numberOfBytes, std::fstream::beg);
            break;

        case FileSeekOrigin::CURSOR:
            _file.seekp(numberOfBytes, std::fstream::cur);
            break;

        case FileSeekOrigin::END:
            _file.seekp(numberOfBytes, std::fstream::end);
            break;

        default:
            std::string errorMessage = "Invalid seek origin provided.";
            Services::get().getLogger()->error("File", errorMessage);
            Services::get().getLogger()->flush();
            throw std::runtime_error(errorMessage);
        }

        if (_file.fail())
        {
            std::string errorMessage = std::string("Failed to seek.");
            Services::get().getLogger()->error("File", errorMessage);
            Services::get().getLogger()->flush();
            throw std::runtime_error(errorMessage);
        }
    }

    std::string File::readWord()
    {
        if (!isOpen())
        {
            std::string errorMessage = "Cannot read from an unopened file.";
            LeoEngine::Services::get().getLogger()->error("File", errorMessage);
            LeoEngine::Services::get().getLogger()->flush();
            throw errorMessage;
        }

        std::string word;

        _file >> word;

        return word;
    }

    std::string File::readLine()
    {
        if (!isOpen())
        {
            std::string errorMessage = "Cannot read from an unopened file.";
            LeoEngine::Services::get().getLogger()->error("File", errorMessage);
            LeoEngine::Services::get().getLogger()->flush();
            throw errorMessage;
        }

        std::string line;

        std::getline(_file, line);

        return line;
    }

    /*
    std::string File::readBytes(int numberOfBytes)
    {
        if (!isOpen())
        {
            std::string errorMessage = "Cannot read from an unopened file.";
            LeoEngine::Services::get().getLogger()->error("File", errorMessage);
            LeoEngine::Services::get().getLogger()->flush();
            throw errorMessage;
        }

        std::string content;

        _file.read(
    }
    */

    void File::write(std::string data)
    {
        if (!isOpen())
        {
            std::string errorMessage = "Cannot write from an unopened file.";
            LeoEngine::Services::get().getLogger()->error("File", errorMessage);
            LeoEngine::Services::get().getLogger()->flush();
            throw errorMessage;
        }

        if (data.empty())
        {
            return;
        }

        _file << data;
        if (_file.fail())
        {
            std::string errorString = "Failed to write data '" + data + "' to file '" + _filepath + "'.";
            Services::get().getLogger()->error("File", errorString);
            Services::get().getLogger()->flush();
            throw std::runtime_error(errorString);
        }
    }

}

