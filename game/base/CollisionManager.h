#ifndef SHMUP_COLLISIONMANAGER_H
#define SHMUP_COLLISIONMANAGER_H

#include <vector>
#include "GameObject.h"

class CollisionManager {
public:
    virtual void checkCollisions(std::vector<GameObject *> const &objects);

private:
    bool checkCollision(Collidable *p1, Collidable *p2);
};


#endif //SHMUP_COLLISIONMANAGER_H
