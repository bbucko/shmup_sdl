#ifndef SHMUP_TILELAYER_H
#define SHMUP_TILELAYER_H

#include "Layer.h"
#include "Level.h"

class TileLayer : public Layer {
public:
    TileLayer(int tileSize, int mapWidth, int mapHeight, const std::vector<Tileset> &tilesets, std::vector<std::vector<int>> tileIDs)
            : m_numColumns(mapWidth), m_numRows(mapHeight), m_tileSize(tileSize), m_tilesets(tilesets), m_tileIDs(std::move(tileIDs)) {};

    void render() override;

    void update() override {};

private:
    Tileset getTilesetByID(int id);

    int m_numColumns;

    int m_numRows;

    int m_tileSize;

    const std::vector<Tileset> &m_tilesets;

    std::vector<std::vector<int>> m_tileIDs;
};

#endif  // SHMUP_TILELAYER_H
