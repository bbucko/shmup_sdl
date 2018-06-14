#include <utils/Logger.h>
#include "GameState.h"
#include "StateParser.h"
#include "ServiceLocator.h"

void GameState::render() {
    for (auto object : m_objects) { object->draw(); }
}

void GameState::update() {
    for (auto object : m_objects) { object->update(); }
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

    }
    return true;
}

GameState::~GameState() {
  DELETE_VECTOR(m_objects);

    for (const auto &textureId : m_textureIds) {
        ServiceLocator::textureManager()->clear(textureId);
    }
    m_textureIds.clear();
};
