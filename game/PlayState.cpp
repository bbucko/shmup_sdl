#include "PlayState.h"

#include <TextureManager.h>
#include <Player.h>
#include <Enemy.h>
#include <Game.h>
#include <base/StateParser.h>
#include <base/BulletHandler.h>

const std::string PlayState::s_playID = "PLAY";

void PlayState::update() {
    for (auto object : objects) {
        object->update();
    }

    BulletHandler::Instance().update();

    calculateCollisions();
}

void PlayState::render() {
    for (auto object : objects) {
        object->draw();
    }

    BulletHandler::Instance().render();

}

bool PlayState::onEnter() {
    LOG_INFO("entering PlayState");

    SDL_Renderer *m_pRenderer = Game::Instance().getRenderer();

    SDL_SetRenderDrawColor(m_pRenderer, 0, 67, 170, 255);

    StateParser stateParser;
    stateParser.parseState("asset/game.xml", s_playID, &objects);

    TextureManager::Instance().load("assets/plane.png", "plane", m_pRenderer);
    TextureManager::Instance().load("assets/whitePlane.png", "whitePlane", m_pRenderer);
    TextureManager::Instance().load("assets/bullet.png", "bullet", m_pRenderer);

    auto *player = new Player();
    player->load(new LoaderParams(320, 400, 65, 65, "plane"));
    objects.push_back(player);

    auto enemy = new Enemy();
    enemy->load(new LoaderParams(320, 0, 65, 65, "whitePlane"));
    objects.push_back(enemy);

    return true;
}

bool PlayState::onExit() {
    LOG_INFO("exiting PlayState");

    for (auto object : objects) {
        object->clean();
    }

    objects.clear();

    TextureManager::Instance().clear("plane");
    TextureManager::Instance().clear("bullet");
    TextureManager::Instance().clear("whitePlane");

    return true;
}

void PlayState::calculateCollisions() {
    std::vector<GameObject *> objectCollisionDetection = objects;

    auto external = objectCollisionDetection.begin();
    while (external != objectCollisionDetection.end()) {
        auto internal = objectCollisionDetection.begin();
        while (internal != objectCollisionDetection.end()) {
            if (internal != external) {
                auto *p1 = dynamic_cast<SDLGameObject *>(*internal);
                auto *p2 = dynamic_cast<SDLGameObject *>(*external);
                if (checkCollision(p1, p2)) {
                    LOG_INFO("Collided: " << p1 << " and " << p2);
                }
            }
            internal++;
        }
        external = objectCollisionDetection.erase(external);
    }
}

bool PlayState::checkCollision(SDLGameObject *p1, SDLGameObject *p2) {
    float leftA, leftB;
    float rightA, rightB;
    float topA, topB;
    float bottomA, bottomB;

    leftA = p1->getPosition().x;
    rightA = p1->getPosition().x + p1->getWidth();
    topA = p1->getPosition().y;
    bottomA = p1->getPosition().y + p1->getHeight();

    //Calculate the sides of rect B
    leftB = p2->getPosition().x;
    rightB = p2->getPosition().x + p2->getWidth();
    topB = p2->getPosition().y;
    bottomB = p2->getPosition().y + p2->getHeight();

    //If any of the sides from A are outside of B
    if (bottomA <= topB) { return false; }
    if (topA >= bottomB) { return false; }
    if (rightA <= leftB) { return false; }
    if (leftA >= rightB) { return false; }

    return true;
}
