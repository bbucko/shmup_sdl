

#ifndef SHMUP_BULLETMANAGER_H
#define SHMUP_BULLETMANAGER_H

#include <vector>
#include <chrono>
#include "GameObject.h"

class BulletHandler {
private:

    std::vector<GameObject *> bullets;

    std::chrono::system_clock::time_point m_lastPlayerShootAt;

public:

    ~BulletHandler() {
        for (auto bullet : bullets) {
            delete bullet;
        }
    }

    void playerShoots(int x, int y);

    void enemyShoots(int x, int y);

    void update();

    void render();
};


#endif //SHMUP_BULLETMANAGER_H
