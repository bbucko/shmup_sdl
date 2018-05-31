#include <SDL.h>
#include "GameObject.h"

#ifndef SHMUP_PLAYER_H
#define SHMUP_PLAYER_H


class Player : public GameObject {
public:
    void update() override;
};


#endif //SHMUP_PLAYER_H
