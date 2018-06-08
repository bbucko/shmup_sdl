#ifndef SHMUP_LEVELPARSER_H
#define SHMUP_LEVELPARSER_H

#include <tinyxml2.h>
#include "Level.h"

using namespace tinyxml2;

class LevelParser;

typedef void (LevelParser::*elementProcessor)(XMLElement *, Level *);

class LevelParser {
public:
    static LevelParser &Instance() {
        static LevelParser instance;
        return instance;
    }

    Level *parseLevel(const char *levelFile);

private:
    int m_tileSize;
    int m_width;

    int m_height;

    char *m_dir;

    LevelParser() = default;

    ~LevelParser() = default;

    void parseTilesets(XMLElement *pTilesetRoot, Level *pLevel);

    void parseTileLayer(XMLElement *pTilesetRoot, Level *pLevel);

    void parseObjectLayer(XMLElement *pObjectElement, Level *pLevel);

    void parseTextures(XMLElement *pTextureRoot);

    void copyIdsToVector(std::vector<std::vector<int>> &data, const std::vector<unsigned int> &gids) const;

    std::vector<std::vector<int>> prepareData() const;

    std::vector<unsigned> prepareIds(const std::string &decodedIDs) const;

    inline void attributeToInt(const XMLAttribute *a, const char *attrName, int *attr) const;

    inline void attributeToString(const XMLAttribute *a, const char *attrName, std::string *attr) const;

    inline void processElement(XMLElement *pElementRoot, std::string elementValue, Level *pLevel, elementProcessor fn);

    XMLError loadRootXML(const char *levelFile, XMLDocument &doc);
};

#endif  // SHMUP_LEVELPARSER_H
