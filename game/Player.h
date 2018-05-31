#ifndef SHMUP_PLAYER_H
#define SHMUP_PLAYER_H

#include "sdl/SDLGameObject.h"

class Player : public SDLGameObject {
public:
    explicit Player(const LoaderParams *pParams) : SDLGameObject(pParams) {
        m_velocity = Vector2D(1, 0);
    };

    void update() override;
};


#endif //SHMUP_PLAYER_H
