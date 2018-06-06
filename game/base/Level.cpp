#include <utils/Logger.h>
#include "Level.h"

void Level::render() {
    for (auto layer : m_layers) {
        layer->render();
    }
}

void Level::update() {
    for (auto layer : m_layers) {
        layer->update();
    }
}

void Level::clean() {

}

void Level::load(const LoaderParams *pParams) {
    LOG_INFO("abc" << pParams);
}

std::vector<Tileset> *Level::getTilesets() {
    return &m_tilesets;
}


std::vector<Layer *> *Level::getLayers() {
    return &m_layers;
}