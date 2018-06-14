#ifndef SHMUP_COLLISIONMANAGER_H
#define SHMUP_COLLISIONMANAGER_H

#include <vector>
#include "GameObject.h"

class CollisionManager {
public:
    virtual void checkCollisions(std::vector<GameObject *> objects);
};


#endif //SHMUP_COLLISIONMANAGER_H
