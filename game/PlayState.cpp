#include "PlayState.h"
#include "ServiceLocator.h"
#include <Game.h>
#include <base/LevelParser.h>

void PlayState::update() {
    GameState::update();

    ServiceLocator::bulletHandler()->update();

    calculateCollisions();
}

void PlayState::render() {
    GameState::render();

    ServiceLocator::bulletHandler()->render();
}

bool PlayState::onEnter() {
    GameState::onEnter();
    LevelParser::Instance().parseLevel("");

    SDL_SetRenderDrawColor(ServiceLocator::renderer(), 0, 67, 170, 255);

    return true;
}

void PlayState::calculateCollisions() {
    std::vector<GameObject *> objectCollisionDetection = m_objects;

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
