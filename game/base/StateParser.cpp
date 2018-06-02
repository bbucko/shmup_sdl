#include "StateParser.h"
#include "Logger.h"

using namespace tinyxml2;

bool StateParser::parseState(const char *stateFile, std::string stateID, std::vector<GameObject *> *pObjects) {
    XMLDocument doc;
    if (!doc.LoadFile(stateFile)) {
        LOG_ERROR(doc.ErrorStr());
    };
    XMLElement *pRoot = doc.RootElement();

    return false;
}

void StateParser::parseTextures(tinyxml2::XMLElement *pStateRoot, std::vector<std::string> *pTextureIDs) {

}

void StateParser::parseObjects(tinyxml2::XMLElement *pStateRoot, std::vector<GameObject *> *pObjects) {

}
