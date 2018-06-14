#ifndef SHMUP_ENEMY_H
#define SHMUP_ENEMY_H

#include "base/GameObjectFactory.h"
#include "sdl/SDLGameObject.h"

class Enemy : public SDLGameObject {
public:
    explicit Enemy(int id) : SDLGameObject(id) {};

    void draw() override;

    void update() override;

    void load(std::unique_ptr<LoaderParams> pParams) override;
};

class EnemyCreator : public BaseCreator {
    GameObject *createGameObject(int id) const override {
        return new Enemy(id);
    }
};

#endif  // SHMUP_ENEMY_H
