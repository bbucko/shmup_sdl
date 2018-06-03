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
    m_playBtn->draw();
    m_exitBtn->draw();
}

bool MenuState::onEnter() {
    LOG_INFO("entering MenuState");
    SDL_Renderer *m_pRenderer = Game::Instance().getRenderer();;
    SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);

    std::vector<std::string> textureIds = std::vector<std::string>();
    StateParser().parseState("assets/game.xml", s_menuID, &m_objects, &textureIds);

    m_playBtn = new MenuButton();
    m_playBtn->load(new LoaderParams(100, 100, 400, 100, "playBtn"));

    m_exitBtn = new MenuButton();
    m_exitBtn->load(new LoaderParams(100, 300, 400, 100, "exitBtn"));

    return true;
}

bool MenuState::onExit() {
    LOG_INFO("exiting MenuState");
    m_exitBtn->clean();
    m_playBtn->clean();
    TextureManager::Instance().clear("exitBtn");
    TextureManager::Instance().clear("playBtn");
    return true;
}