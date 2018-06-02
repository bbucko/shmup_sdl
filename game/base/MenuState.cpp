#include "MenuState.h"

#include <iostream>
#include <SDL.h>
#include <Game.h>

const std::string MenuState::s_menuID = "MENU";

void MenuState::update() {
    // nothing for now
}

void MenuState::render() {
    // nothing for now
}

bool MenuState::onEnter() {
    LOG("entering MenuState");
    SDL_Renderer *m_pRenderer = Game::Instance().getRenderer();
    SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);

    return true;
}

bool MenuState::onExit() {
    LOG("exiting MenuState");
    return true;
}