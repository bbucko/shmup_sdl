#include "CollisionManager.h"

void CollisionManager::checkCollisions(std::vector<GameObject *> const &objects) {
    for (auto object : objects) {
        auto positionable1 = dynamic_cast<Collidable *>(object);

        for (auto collider : objects) {
            auto positionable2 = dynamic_cast<Collidable *>(collider);

            if (object->getId() != collider->getId()) {
                if (checkCollision(positionable1, positionable2)) {
//                    LOG_INFO("Collided");
                    positionable1->collided(*positionable2);
                    positionable2->collided(*positionable1);
                };
            }
        }
    }
}

bool CollisionManager::checkCollision(Collidable *p1, Collidable *p2) {
    float leftA, leftB;
    float rightA, rightB;
    float topA, topB;
    float bottomA, bottomB;

    leftA = p1->upperLeft().x;
    rightA = p1->lowerRight().x;

    topA = p1->upperLeft().y;
    bottomA = p1->lowerRight().y;

    // Calculate the sides of rect B
    leftB = p2->upperLeft().x;
    rightB = p2->lowerRight().x;
    topB = p2->upperLeft().y;
    bottomB = p2->lowerRight().y;

    // If any of the sides from A are outside of B
    if (bottomA <= topB) { return false; }
    if (topA >= bottomB) { return false; }
    if (rightA <= leftB) { return false; }
    if (leftA >= rightB) { return false; }

    return true;
}