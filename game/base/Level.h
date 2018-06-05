#ifndef SHMUP_LEVEL_H
#define SHMUP_LEVEL_H

#include <sdl/SDLGameObject.h>
#include <vector>
#include "GameObject.h"
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

class Level : public SDLGameObject {
public:
    void draw() override;

    void update() override;

    void clean() override;

    void load(const LoaderParams *pParams) override;

private:
    std::vector<Tileset> m_tilesets;
    std::vector<Layer *> m_layers;

};


#endif //SHMUP_LEVEL_H
