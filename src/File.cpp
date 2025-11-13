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
    
    File::File(std::string filepath, bool isBinary)
        : _filepath(filepath), _isBinary(isBinary),
          _sdlFile(NULL), _isOpen(false)
    {
        char *defaultPrefPath = SDL_GetPrefPath("LeoDefaultOrg", "LeoDefaultApp");
        _writeDirectory = defaultPrefPath;
        SDL_free(defaultPrefPath);
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
            std::string errorMessage = "Re-creating file '" + _filepath + "', which is already open.";
            Services::get().getLogger()->error("File", errorMessage);
            Services::get().getLogger()->flush();
            throw std::runtime_error(errorMessage);
        }

        _sdlFile = SDL_IOFromFile(_filepath.c_str(), "w+");
        if (_sdlFile == NULL)
        {
            _isOpen = false;
            std::string errorMessage = "Failed to create file '" + _filepath + "'. SDL error text: '" + SDL_GetError() + "'.";
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

        _sdlFile = SDL_IOFromFile(_filepath.c_str(), "r+");
        if (_sdlFile == NULL)
        {
            _isOpen = false;
            std::string errorMessage = "Failed to create file '" + _filepath + "'. SDL error text: '" + SDL_GetError() + "'.";
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

        SDL_CloseIO(_sdlFile);
        _sdlFile = NULL;
        _isOpen = false;
    }

    bool File::exists() const
    {
        return SDL_GetPathInfo(_filepath.c_str(), NULL);
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
            seekResult = SDL_SeekIO(_sdlFile, numberOfBytes, SDL_IO_SEEK_SET);
            break;
        case FileSeekOrigin::CURSOR:
            seekResult = SDL_SeekIO(_sdlFile, numberOfBytes, SDL_IO_SEEK_CUR);
            break;
        case FileSeekOrigin::END:
            seekResult = SDL_SeekIO(_sdlFile, numberOfBytes, SDL_IO_SEEK_END);
            break;
        default:
            std::string errorMessage = "Invalid seek origin provided.";
            Services::get().getLogger()->error("File", errorMessage);
            Services::get().getLogger()->flush();
            throw std::runtime_error(errorMessage);
        }

        if (seekResult < 0)
        {
            std::string errorMessage = std::string("Failed to seek. SDL error text: '") + SDL_GetError() + "'.";
            Services::get().getLogger()->error("File", errorMessage);
            Services::get().getLogger()->flush();
            throw std::runtime_error(errorMessage);
        }
    }

    std::string File::read(int numberOfBytes)
    {
        char *inputBuffer = new char[numberOfBytes];
        void *voidInputBuffer = static_cast<void *>(inputBuffer);

        if (SDL_GetIOStatus(_sdlFile) == SDL_IO_STATUS_EOF)
        {
            return "";
        }

        SDL_ReadIO(_sdlFile, voidInputBuffer, numberOfBytes);
        std::string inputString(inputBuffer);

        delete[] inputBuffer;

        if (inputString.empty())
        {
            std::string errorMessage = "Failed to read from file '" + _filepath + "'. SDL error text: '" + SDL_GetError() + "'.";
            Services::get().getLogger()->error("File", errorMessage);
            Services::get().getLogger()->flush();
            throw std::runtime_error(errorMessage);
        }

        return inputString;
    }

    void File::write(std::string data)
    {
        if (data.size() < 1)
        {
            return;
        }

        const char *cStringData = data.c_str();
        const void *voidData = static_cast<const void *>(cStringData);

        int writeResult = SDL_WriteIO(_sdlFile, voidData, data.size());
        if (writeResult < data.size())
        {
            std::string errorString = "Failed to write data '" + data + "' to file '" + _filepath + "'. SDL error text: '" + SDL_GetError() + "'.";
            Services::get().getLogger()->error("File", errorString);
            Services::get().getLogger()->flush();
            throw std::runtime_error(errorString);
        }
    }

}

