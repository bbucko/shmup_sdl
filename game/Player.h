#ifndef SHMUP_PLAYER_H
#define SHMUP_PLAYER_H

#include "base/GameObjectFactory.h"
#include "sdl/SDLGameObject.h"

class Player : public SDLGameObject {
public:
    void update() override;

    void load(const LoaderParams *pParams) override;
};

class PlayerCreator : public BaseCreator {
    GameObject *createGameObject() const override {
        return new Player();
    }
};

#endif //SHMUP_PLAYER_H
