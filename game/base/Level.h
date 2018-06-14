#ifndef SHMUP_LEVEL_H
#define SHMUP_LEVEL_H

#include "Layer.h"
#include "sdl/SDLGameObject.h"

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
    void render();

    void update();

    void clean();

    void load(const LoaderParams *pParams);

    std::vector<Tileset> *getTilesets() { return &m_tilesets; }


    std::vector<Layer *> *getLayers() { return &m_layers; }

    ~Level() {
        m_tilesets.clear();

        for (auto layer : m_layers) {
            delete layer;
        }
        m_layers.clear();
    }

private:
    friend class LevelParser;

    Level() = default;

    std::vector<Tileset> m_tilesets;

    std::vector<Layer *> m_layers;
};

#endif  // SHMUP_LEVEL_H
