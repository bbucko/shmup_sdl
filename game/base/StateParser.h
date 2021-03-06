#ifndef SHMUP_STATEPARSER_H
#define SHMUP_STATEPARSER_H

#include <tinyxml2.h>
#include <string>
#include <vector>
#include "GameObject.h"

class StateParser {
public:
    bool parseState(const char *stateFile, std::string stateID, std::vector<GameObject *> *pObjects, std::vector<std::string> *pTextureIDs);

private:
    void parseObjects(tinyxml2::XMLElement *pStateRoot, std::vector<GameObject *> *pObjects);

    void parseTextures(tinyxml2::XMLElement *pStateRoot, std::vector<std::string> *pTextureIDs);
};

#endif  // SHMUP_STATEPARSER_H
