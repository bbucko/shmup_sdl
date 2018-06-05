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

    const char * m_dir;

    LevelParser() = default;

    ~LevelParser() = default;

    void parseTilesets(XMLElement *pTilesetRoot, std::vector<Tileset> *pTilesets);

    void parseTileLayer(XMLElement *pTileElement, std::vector<Layer *> *pLayers, const std::vector<Tileset> *pTilesets);
    void copyIdsToVector(std::vector<std::vector<int>> &data, const std::vector<unsigned int> &gids) const;
public:

    static LevelParser &Instance() {
        static LevelParser instance;
        return instance;
    }

    Level *parseLevel(const char *levelFile);

    std::vector<std::vector<int>> prepareData() const;

    std::vector<unsigned> prepareIds(const std::string &decodedIDs) const;
};


#endif //SHMUP_LEVELPARSER_H
