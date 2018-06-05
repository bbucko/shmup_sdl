#ifndef SHMUP_LEVEL_H
#define SHMUP_LEVEL_H

#include <sdl/SDLGameObject.h>
#include "Layer.h"

struct Tileset {
    int firstGridID;
    int tileWidth;
    int tileHeight;
    int spacing;
    int margin;
    int width;
    int height;
    int numColumns;
    std::string name;
};

class Level {
public:
    void draw();

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
