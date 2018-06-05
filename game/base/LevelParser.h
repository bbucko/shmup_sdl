#ifndef SHMUP_LEVELPARSER_H
#define SHMUP_LEVELPARSER_H

#include <tinyxml2.h>
#include "Level.h"

using namespace tinyxml2;

class LevelParser {
private:
    LevelParser() = default;

    ~LevelParser() = default;

    void parseTilesets(XMLElement *pTilesetRoot, std::vector<Tileset> *pTilesets);

    void parseTileLayer(XMLElement *pTileElement, std::vector<Layer *> *pLayers, const std::vector<Tileset> *pTilesets);

    int m_tileSize;
    int m_width;
    int m_height;

    const char * m_dir;

public:
    static LevelParser &Instance() {
        static LevelParser instance;
        return instance;
    }

    Level *parseLevel(const char *levelFile);
};


#endif //SHMUP_LEVELPARSER_H
