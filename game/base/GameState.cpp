#include <TextureManager.h>
#include "GameState.h"
#include "Logger.h"
#include "StateParser.h"

void GameState::render() {
    for (auto object : m_objects) {
        object->draw();
    }
}

void GameState::update() {
    for (auto object : m_objects) {
        object->update();
    }
}

bool GameState::onEnter() {
    LOG_INFO("entering state: " << getStateID());
    StateParser().parseState("assets/game.xml", getStateID(), &m_objects, &m_textureIds);
    return true;
}

bool GameState::onExit() {
    LOG_INFO("exiting state: " << getStateID());
    for (auto object : m_objects) {
        object->clean();
        delete object;
    }
    m_objects.clear();

    for (auto textureId : m_textureIds) {
        TextureManager::Instance().clear(textureId);
    }
    m_textureIds.clear();
    return true;
}