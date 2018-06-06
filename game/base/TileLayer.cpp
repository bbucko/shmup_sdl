#include <Game.h>
#include <ServiceLocator.h>
#include "TileLayer.h"

TileLayer::TileLayer(int tileSize, const std::vector<Tileset> &tilesets, std::vector<std::vector<int>> tileIDs)
        : m_tileSize(tileSize), m_position(0, 0), m_velocity(0, 0), m_tilesets(tilesets), m_tileIDs(std::move(tileIDs)) {
    LOG_INFO("Data: " << m_tileIDs.size());
    const vec2 &dimensions = Game::Instance().getDimensions();

    m_numColumns = static_cast<int>(dimensions.x / m_tileSize);
    m_numRows = static_cast<int>(dimensions.y / m_tileSize);

    LOG_INFO("numColumns: " << m_numColumns << " numRows: " << m_numRows);
}

void TileLayer::render() {
    int x, y, x2, y2 = 0;

    x = static_cast<int>(m_position.x / m_tileSize);
    y = static_cast<int>(m_position.y / m_tileSize);

    x2 = static_cast<int>(m_position.x) % m_tileSize;
    y2 = static_cast<int>(m_position.y) % m_tileSize;

    for (int i = 0; i < m_numRows; i++) {
        for (int j = 0; j < m_numColumns; j++) {
            std::vector<int> &row = m_tileIDs.at(i);
            int id = row.at(static_cast<unsigned long>(j + x));

            if (id == 0) {
                continue;
            }

            Tileset tileset = getTilesetByID(id);

            id--;

            drawTile(tileset, (j * m_tileSize) - x2, (i * m_tileSize) - y2,
                     (id - (tileset.firstGridID - 1)) / tileset.numColumns,
                     (id - (tileset.firstGridID - 1)) % tileset.numColumns);
        }
    }
}

void TileLayer::drawTile(const Tileset &tileset, int x, int y, int row, int frame) const {
    ServiceLocator::textureManager()->drawTile(tileset.name, tileset.margin, tileset.spacing, x, y, m_tileSize, m_tileSize, row, frame, ServiceLocator::renderer());
}

void TileLayer::update() {
    m_position += m_velocity;
}

Tileset TileLayer::getTilesetByID(int tileID) {
    for (int i = 0; i < m_tilesets.size(); i++) {
        if (i + 1 <= m_tilesets.size() - 1) {

            if (tileID >= m_tilesets[i].firstGridID && tileID < m_tilesets[i + 1].firstGridID) {
                return m_tilesets[i];
            }
        } else {
            return m_tilesets[i];
        }
    }

    LOG_INFO("did not find tileset, returning empty tileset");
    Tileset t;
    return t;
}

