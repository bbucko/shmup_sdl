#include "ObjectLayer.h"
#include <utils/Logger.h>

void ObjectLayer::update() {
    for (auto object : m_objects) {
        object->update();
    }
    calculateCollisions();
}

void ObjectLayer::render() {
    for (auto object : m_objects) {
        object->draw();
    }
}

std::vector<GameObject *> *ObjectLayer::getObjects() {
    return &m_objects;
}

void ObjectLayer::calculateCollisions() {
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

bool ObjectLayer::checkCollision(SDLGameObject *p1, SDLGameObject *p2) {
    float leftA, leftB;
    float rightA, rightB;
    float topA, topB;
    float bottomA, bottomB;

    leftA = p1->getPosition().x;
    rightA = p1->getPosition().x + p1->getWidth();
    topA = p1->getPosition().y;
    bottomA = p1->getPosition().y + p1->getHeight();

    // Calculate the sides of rect B
    leftB = p2->getPosition().x;
    rightB = p2->getPosition().x + p2->getWidth();
    topB = p2->getPosition().y;
    bottomB = p2->getPosition().y + p2->getHeight();

    // If any of the sides from A are outside of B
    if (bottomA <= topB) { return false; }
    if (topA >= bottomB) { return false; }
    if (rightA <= leftB) { return false; }
    if (leftA >= rightB) { return false; }

    return true;
}