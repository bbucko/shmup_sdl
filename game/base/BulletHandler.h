#ifndef SHMUP_BULLETMANAGER_H
#define SHMUP_BULLETMANAGER_H

#include <chrono>
#include <vector>
#include <utils/Memory.h>
#include "GameObject.h"

class BulletHandler {
public:
    void playerShoots(int x, int y);

    void enemyShoots(int x, int y);

    void update();

    void render() const;

    ~BulletHandler() { DELETE_VECTOR(m_bullets); }

private:
    std::vector<GameObject *> m_bullets;

    std::chrono::system_clock::time_point m_lastPlayerShootAt;
};

#endif  // SHMUP_BULLETMANAGER_H
