#include "MenuState.h"

#include <SDL.h>
#include <Game.h>
#include <TextureManager.h>
#include <base/StateParser.h>

bool MenuState::onEnter() {
    GameState::onEnter();
    SDL_SetRenderDrawColor(Game::Instance().getRenderer(), 0, 0, 0, 255);
    return true;
}