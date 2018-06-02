#ifndef SHMUP_ENEMY_H
#define SHMUP_ENEMY_H

#include "base/GameObjectFactory.h"
#include "sdl/SDLGameObject.h"

class Enemy : public SDLGameObject {

public:

    void draw() override;

    void update() override;

    void load(const LoaderParams *pParams) override;
};

class EnemyCreator : public BaseCreator {
    GameObject *createGameObject() const override {
        return new Enemy();
    }
};

#endif //SHMUP_ENEMY_H
