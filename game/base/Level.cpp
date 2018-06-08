#include "Level.h"
#include "utils/Logger.h"

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