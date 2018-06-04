#include "MenuState.h"
#include "ServiceLocator.h"

#include <SDL.h>
#include <Game.h>

bool MenuState::onEnter() {
    GameState::onEnter();
    SDL_SetRenderDrawColor(ServiceLocator::renderer(), 0, 0, 0, 255);
    return true;
}