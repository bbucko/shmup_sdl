#include "StateParser.h"
#include "Logger.h"

using namespace tinyxml2;

bool StateParser::parseState(const char *stateFile, std::string stateID, std::vector<GameObject *> *pObjects) {
    XMLDocument doc;
    XMLError error = doc.LoadFile(stateFile);

    if (error != XML_SUCCESS) {
        LOG_ERROR("Error occurred: " << XMLDocument::ErrorIDToName(error));
    };

    XMLElement *pRoot = doc.RootElement();

    return false;
}

void StateParser::parseTextures(tinyxml2::XMLElement *pStateRoot, std::vector<std::string> *pTextureIDs) {

}

void StateParser::parseObjects(tinyxml2::XMLElement *pStateRoot, std::vector<GameObject *> *pObjects) {

}