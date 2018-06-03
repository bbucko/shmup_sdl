#include <Player.h>
#include <TextureManager.h>
#include <Game.h>
#include "StateParser.h"
#include "StringUtils.h"

using namespace tinyxml2;

bool StateParser::parseState(const char *stateFile, std::string stateID, std::vector<GameObject *> *pObjects, std::vector<std::string> *pTextureIDs) {
    XMLDocument doc;
    XMLError result = doc.LoadFile(stateFile);

    if (result == XML_SUCCESS) {
        XMLElement *pRoot = doc.RootElement();

        if (StringUtils::equalsIgnoreCase(pRoot->Value(), "states")) {
            for (XMLElement *pStateRoot = pRoot->FirstChildElement(); pStateRoot != nullptr; pStateRoot = pStateRoot->NextSiblingElement()) {
                auto stateName = std::string(pStateRoot->Value());
                if (StringUtils::equalsIgnoreCase(stateName, stateID)) {
                    LOG_INFO("Parsing state: " << stateName);

                    for (XMLElement *pElementRoot = pStateRoot->FirstChildElement(); pElementRoot != nullptr; pElementRoot = pElementRoot->NextSiblingElement()) {
                        auto elementValue = std::string(pElementRoot->Value());
                        if (StringUtils::equalsIgnoreCase(elementValue, "textures")) {
                            parseTextures(pElementRoot, pTextureIDs);
                        } else if (StringUtils::equalsIgnoreCase(elementValue, "objects")) {
                            parseObjects(pElementRoot, pObjects);
                        }
                    }
                    return true;
                }
            }
        }
        return false;
    } else {
        LOG_ERROR("Error occurred: " << XMLDocument::ErrorIDToName(result));
    }

    return false;
}

void StateParser::parseTextures(tinyxml2::XMLElement *pElementRoot, std::vector<std::string> *pTextureIDs) {
    LOG_INFO("Parsing textures: " << pElementRoot->Value());
    for (const XMLElement *pStateRoot = pElementRoot->FirstChildElement(); pStateRoot != nullptr; pStateRoot = pStateRoot->NextSiblingElement()) {
        if (StringUtils::equalsIgnoreCase(pStateRoot->Value(), "texture")) {
            std::string filename;
            std::string id;
            for (const XMLAttribute *a = pStateRoot->FirstAttribute(); a; a = a->Next()) {
                if (StringUtils::equalsIgnoreCase(a->Name(), "filename")) {
                    filename = a->Value();
                }

                if (StringUtils::equalsIgnoreCase(a->Name(), "id")) {
                    id = a->Value();
                }
            }

            if (filename != "" && id != "") {
                TextureManager::Instance().load(filename, id, Game::Instance().getRenderer());
                pTextureIDs->push_back(id);
            }
        }
    }
    LOG_INFO("Done parsing textures. Textures found: " << pTextureIDs->size());
}

void StateParser::parseObjects(tinyxml2::XMLElement *pElementRoot, std::vector<GameObject *> *pObjects) {
    LOG_INFO("Parsing objects: " << pElementRoot->Value());
    for (XMLElement *pStateRoot = pElementRoot->FirstChildElement(); pStateRoot != nullptr; pStateRoot = pStateRoot->NextSiblingElement()) {
        pObjects->push_back(new Player());
    }
    LOG_INFO("Done parsing objects. Objects found: " << pObjects->size());
}
