#ifndef SHMUP_ENEMY_H
#define SHMUP_ENEMY_H

#include "sdl/SDLGameObject.h"

class Enemy : public SDLGameObject {

public:

    void draw() override;

    void update() override;

    explicit Enemy(const LoaderParams *pParams) : SDLGameObject(pParams) {
        m_velocity = vec2(1, 0);
    };
};


#endif //SHMUP_ENEMY_H
