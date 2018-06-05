

#include <Game.h>
#include "TileLayer.h"

void TileLayer::render() {

}

void TileLayer::update() {

}

TileLayer::TileLayer(int tileSize, const std::vector<Tileset> &tilesets) : m_tileSize(tileSize), m_tilesets(tilesets), m_position(0, 0), m_velocity(0, 0) {
    const vec2 &dimensions = Game::Instance().getDimensions();
    
    m_numColumns = static_cast<int>(dimensions.x / m_tileSize);
    m_numRows = static_cast<int>(dimensions.y / m_tileSize);
}
