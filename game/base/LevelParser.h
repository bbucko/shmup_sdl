#ifndef SHMUP_LEVELPARSER_H
#define SHMUP_LEVELPARSER_H

#include <tinyxml2.h>
#include "Level.h"

using namespace tinyxml2;

class LevelParser {
private:
    int m_tileSize;
    int m_width;

    int m_height;

    const char *m_dir;

    LevelParser() = default;

    ~LevelParser() = default;

    void parseTilesets(XMLElement *pTilesetRoot, Level *pLevel);

    void parseTileLayer(XMLElement *pTilesetRoot, Level *pLevel);

    void parseObjects(XMLElement *pTilesetRoot, Level *pLevel);

    void copyIdsToVector(std::vector<std::vector<int>> &data, const std::vector<unsigned int> &gids) const;

public:

    static LevelParser &Instance() {
        static LevelParser instance;
        return instance;
    }

    Level *parseLevel(const char *levelFile);

    std::vector<std::vector<int>> prepareData() const;

    std::vector<unsigned> prepareIds(const std::string &decodedIDs) const;

    void attributeToInt(const XMLAttribute *a, const char *attrName, int *attr) const;

    void attributeToString(const XMLAttribute *a, const char *attrName, std::string *attr) const;

    void processElement(XMLElement *pElementRoot, std::string elementValue, Level *pLevel, void (LevelParser::*fn)(XMLElement *, Level *));

    XMLError loadRootXML(const char *levelFile, XMLDocument &doc);
};


#endif //SHMUP_LEVELPARSER_H
