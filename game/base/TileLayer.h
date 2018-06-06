

#ifndef SHMUP_TILELAYER_H
#define SHMUP_TILELAYER_H


#include "Layer.h"
#include "Level.h"

class TileLayer : public Layer {
public:

    TileLayer(int tileSize, const std::vector<Tileset> &tilesets, std::vector<std::vector<int>> vector);

    void render() override;

    void update() override;

private:
    int m_numColumns;
    int m_numRows;
    int m_tileSize;

    vec2 m_position;
    vec2 m_velocity;

    const std::vector<Tileset> &m_tilesets;

    std::vector<std::vector<int>> m_tileIDs;
};


#endif //SHMUP_TILELAYER_H