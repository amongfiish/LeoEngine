#include <memory>

#include "LeoEngine/XMLParser.hpp"
#include "rapidxml/rapidxml_utils.hpp"

namespace LeoEngine
{

    XMLParser::XMLParser(std::string subdirectory)
    {
        std::string basePath = SDL_GetBasePath();

        for (char& c : subdirectory)
        {
            if ((c == '\\' || c == '/') && c != PATH_SEPARATOR)
            {
                c = PATH_SEPARATOR;
            }
        }

        _fullPath = basePath + subdirectory + PATH_SEPARATOR;
    }

    std::unique_ptr<rapidxml::xml_document<>> XMLParser::parseFile(std::string filename)
    {
        rapidxml::file<> file((_fullPath + filename).c_str());
        std::unique_ptr<rapidxml::xml_document<>> document;
        document->parse<0>(file.data());

        return std::move(document);
    }

}

