#include "MenuState.h"

#include <SDL.h>
#include <Game.h>

bool MenuState::onEnter() {
    GameState::onEnter();
    SDL_SetRenderDrawColor(Game::Instance().renderer(), 0, 0, 0, 255);
    return true;
}