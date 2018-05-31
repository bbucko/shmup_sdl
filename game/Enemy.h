#ifndef SHMUP_ENEMY_H
#define SHMUP_ENEMY_H

#include "sdl/SDLGameObject.h"

class Enemy : public SDLGameObject {

public:
    explicit Enemy(const LoaderParams *pParams) : SDLGameObject(pParams) {};
};


#endif //SHMUP_ENEMY_H
