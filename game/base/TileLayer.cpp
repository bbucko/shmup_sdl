#include "TileLayer.h"
#include <Game.h>
#include <ServiceLocator.h>

TileLayer::TileLayer(int tileSize, int mapWidth, int mapHeight, const std::vector<Tileset> &tilesets, std::vector<std::vector<int>> tileIDs)
        : m_tileSize(tileSize), m_tilesets(tilesets), m_tileIDs(std::move(tileIDs)) {

    const vec2 &dimensions = Game::Instance().getDimensions();

    m_numColumns = static_cast<int>(dimensions.x / m_tileSize);
    m_numRows = static_cast<int>(dimensions.y / m_tileSize);

    m_position = vec2(0, m_tileSize * m_numRows);
    m_velocity = vec2(0, 1);
}

void TileLayer::render() {
    int x, y, xFraction, yFraction = 0;

    x = static_cast<int>(m_position.x / m_tileSize);
    y = static_cast<int>(m_position.y / m_tileSize) - 1;
    xFraction = static_cast<int>(m_position.x) % m_tileSize;
    yFraction = static_cast<int>(m_position.y) % m_tileSize;

    for (int i = 0; i < m_numRows; i++) {
        for (int j = 0; j < m_numColumns; j++) {
            int tileY = static_cast<int>(y - i);
            int tileX = static_cast<int>(x + j);

            if (tileY > m_numRows) continue;

            int id = m_tileIDs[tileY][tileX] - 1;
//            LOG_INFO("Tile X: " << tileX << " Y: " << tileY << " value: " << id);

            if (id == -1) continue;

            Tileset tileset = getTilesetByID(id);
            ServiceLocator::textureManager()->drawTile(tileset.name, tileset.margin, tileset.spacing,
                                                       (j * m_tileSize) + xFraction, (i * m_tileSize) + yFraction,
                                                       m_tileSize, m_tileSize,
                                                       (id - (tileset.firstGridID - 1)) / tileset.numColumns, (id - (tileset.firstGridID - 1)) % tileset.numColumns,
                                                       ServiceLocator::renderer());
        }
    }
}

void TileLayer::update() {
    m_position += m_velocity;
}

Tileset TileLayer::getTilesetByID(int tileID) {
    int size = static_cast<int>(m_tilesets.size());
    for (int i = 0; i < size; i++) {
        if (i + 1 <= size - 1) {

            if (tileID >= m_tilesets[i].firstGridID && tileID < m_tilesets[i + 1].firstGridID) {
                return m_tilesets[i];
            }
        } else {
            return m_tilesets[i];
        }
    }

    LOG_INFO("did not find tileset, returning empty tileset");
    Tileset t = {};
    return t;
}