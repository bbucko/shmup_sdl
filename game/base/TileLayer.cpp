#include "TileLayer.h"
#include <Game.h>
#include <base/ServiceLocator.h>

void TileLayer::render() {
    auto position = ServiceLocator::camera()->getPosition();
    auto dimension = Game::Instance().windowSize();

    for (int i = 0; i < m_numRows; i++) {
        for (int j = 0; j < m_numColumns; j++) {
            int id = m_tileIDs[i][j] - 1;
            if (id == -1) continue;

            Tileset tileset = getTilesetByID(id);
            int tilePositionX = static_cast<int>((j * m_tileSize) - position.x);
            int tilePositionY = static_cast<int>((i * m_tileSize) - position.y);
            if (tilePositionX >= 0 - m_tileSize && tilePositionX <= dimension.x + m_tileSize && tilePositionY >= 0 - m_tileSize && tilePositionY <= dimension.y + m_tileSize) {
                ServiceLocator::textureManager()->draw(tileset.name, tileset.margin, tileset.spacing,
                                                       tilePositionX, tilePositionY,
                                                       m_tileSize, m_tileSize,
                                                       (id - (tileset.firstGridID - 1)) / tileset.numColumns, (id - (tileset.firstGridID - 1)) % tileset.numColumns);
            }
        }
    }
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