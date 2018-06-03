

#ifndef SHMUP_BULLETMANAGER_H
#define SHMUP_BULLETMANAGER_H

#include <vector>
#include "GameObject.h"

class BulletHandler {
private:

    std::vector<GameObject *> bullets;

    std::chrono::system_clock::time_point m_lastPlayerShootAt;

public:

    void playerShoots(int x, int y);

    void enemyShoots(int x, int y);

    void update();

    void render();

    static BulletHandler &Instance() {
        static BulletHandler instance;
        return instance;
    }
};


#endif //SHMUP_BULLETMANAGER_H
