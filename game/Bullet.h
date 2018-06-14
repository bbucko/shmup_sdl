#ifndef SHMUP_BULLET_H
#define SHMUP_BULLET_H

#include <base/GameObjectFactory.h>
#include "sdl/SDLGameObject.h"

class Bullet : public SDLGameObject {
public:
    explicit Bullet(int id) : SDLGameObject(id) {}

    void load(std::unique_ptr<LoaderParams> pParams) override;

    void update() override;
};

class BulletCreator : public BaseCreator {
    GameObject *createGameObject(int id) const override {
        return new Bullet(id);
    }
};

#endif  // SHMUP_BULLET_H
