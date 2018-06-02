#include "PlayState.h"

#include <TextureManager.h>
#include <Player.h>
#include <Enemy.h>
#include <Game.h>

const std::string PlayState::s_playID = "PLAY";

void PlayState::update() {
    for (auto object : objects) {
        object->update();
    }
}

void PlayState::render() {
    for (auto object : objects) {
        object->draw();
    }
}

bool PlayState::onEnter() {
    LOG("entering PlayState");

    SDL_Renderer *m_pRenderer = Game::Instance().getRenderer();

    SDL_SetRenderDrawColor(m_pRenderer, 0, 67, 170, 255);
    TextureManager::Instance().load("assets/plane.png", "plane", m_pRenderer);
    TextureManager::Instance().load("assets/whitePlane.png", "whitePlane", m_pRenderer);

    objects.push_back(new Player(new LoaderParams(320, 400, 65, 65, "plane")));
    objects.push_back(new Enemy(new LoaderParams(320, 0, 65, 65, "whitePlane")));
    return true;
}

bool PlayState::onExit() {
    LOG("exiting PlayState");

    for (auto object : objects) {
        object->clean();
    }

    return true;
}