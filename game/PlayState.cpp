#include "PlayState.h"

#include <TextureManager.h>
#include <Game.h>
#include <base/StateParser.h>
#include <base/BulletHandler.h>

const std::string PlayState::s_playID = "PLAY";

void PlayState::update() {
    for (auto object : m_objects) {
        object->update();
    }

    BulletHandler::Instance().update();

    calculateCollisions();
}

void PlayState::render() {
    for (auto object : m_objects) {
        object->draw();
    }

    BulletHandler::Instance().render();
}

bool PlayState::onEnter() {
    LOG_INFO("entering PlayState");

    SDL_SetRenderDrawColor(Game::Instance().getRenderer(), 0, 67, 170, 255);
    StateParser().parseState("assets/game.xml", s_playID, &m_objects, &m_textureIds);

    return true;
}

bool PlayState::onExit() {
    LOG_INFO("exiting PlayState");

    for (auto object : m_objects) {
        object->clean();
    }

    m_objects.clear();

    for (auto textureId : m_textureIds) {
        TextureManager::Instance().clear(textureId);
    }
    m_textureIds.clear();

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
