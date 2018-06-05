#include <utility>


#include <Game.h>
#include "TileLayer.h"

void TileLayer::render() {

}

void TileLayer::update() {

}

TileLayer::TileLayer(int tileSize, const std::vector<Tileset> &tilesets, std::vector<std::vector<int>> vector)
        : m_tileSize(tileSize), m_position(0, 0), m_velocity(0, 0), m_tilesets(tilesets), m_tileIDs(std::move(vector)) {
    const vec2 &dimensions = Game::Instance().getDimensions();

    m_numColumns = static_cast<int>(dimensions.x / m_tileSize);
    m_numRows = static_cast<int>(dimensions.y / m_tileSize);
}

