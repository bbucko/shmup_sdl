#include <utils/Logger.h>
#include "Level.h"

void Level::draw() {
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
