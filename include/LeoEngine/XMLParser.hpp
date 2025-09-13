#ifndef XML_PARSER_HPP
#define XML_PARSER_HPP

#include <string>
#include <memory>
#if defined(__linux__) || defined(__APPLE__)
    #include <SDL2/SDL.h>
#elif defined(_WIN32)
    #include <SDL.h>
#endif

#include "rapidxml/rapidxml.hpp"

namespace LeoEngine
{

#ifdef _WIN32
#define PATH_SEPARATOR '\\'
#else
#define PATH_SEPARATOR '/'
#endif

    // this needs some work but it's a temporary solution to the need for
    // an xml parser for LeoParty
    class XMLParser
    {
    public:
        // this subdirectory is different from the usual one
        // as it is the subdirectory within resources/xml,
        // not just resources.
        XMLParser(std::string subdirectory);

        std::unique_ptr<rapidxml::xml_document<>> parseFile(std::string filename);
    
    private:
        std::string _fullPath;
    };

}

#endif

