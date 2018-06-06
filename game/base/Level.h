#ifndef SHMUP_LEVEL_H
#define SHMUP_LEVEL_H

#include <sdl/SDLGameObject.h>
#include "Layer.h"

struct Tileset {
    std::string name;
    int firstGridID;

    int tileWidth;
    int tileHeight;

    int spacing;
    int margin;

    int width;
    int height;

    int numColumns;
};

class Level {
public:
    void render();

    void update();

    void clean();

    void load(const LoaderParams *pParams);

    std::vector<Tileset> *getTilesets();

    std::vector<Layer *> *getLayers();

private:

    friend class LevelParser;

    Level() = default;

    std::vector<Tileset> m_tilesets;

    std::vector<Layer *> m_layers;
};


#endif //SHMUP_LEVEL_H
