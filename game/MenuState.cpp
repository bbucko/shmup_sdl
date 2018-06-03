#include "MenuState.h"

#include <SDL.h>
#include <Game.h>
#include <TextureManager.h>
#include <base/StateParser.h>

const std::string MenuState::s_menuID = "MENU";

void MenuState::update() {
    // nothing for now
}

void MenuState::render() {
    for (auto object : m_objects) {
        object->draw();
    }
}

bool MenuState::onEnter() {
    LOG_INFO("entering MenuState");
    SDL_Renderer *m_pRenderer = Game::Instance().getRenderer();;
    SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);

    StateParser().parseState("assets/game.xml", s_menuID, &m_objects, &m_textureIds);

    return true;
}

bool MenuState::onExit() {
    LOG_INFO("exiting MenuState");

    for (auto object : m_objects) {
        object->clean();
    }

    for (auto object : m_textureIds) {
        TextureManager::Instance().clear("object");
    }

    return true;
}