#include "PlayState.h"
#include <Game.h>
#include <base/LevelParser.h>
#include "base/ServiceLocator.h"

void PlayState::update() {
    ServiceLocator::camera()->update();
    pLevel->update();
}

void PlayState::render() {
    pLevel->render();
}

bool PlayState::onEnter() {
    GameState::onEnter();
    pLevel = LevelParser::Instance().parseLevel("assets/map1.tmx");

    SDL_SetRenderDrawColor(Game::Instance().renderer(), 0, 67, 170, 255);

    return true;
}
