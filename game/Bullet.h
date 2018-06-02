#ifndef SHMUP_BULLET_H
#define SHMUP_BULLET_H

#include <base/GameObjectFactory.h>
#include "sdl/SDLGameObject.h"

class Bullet : public SDLGameObject {
public:
    void load(const LoaderParams *pParams) override;

    void update() override;
};

class BulletCreator : public BaseCreator {
    GameObject *createGameObject() const override {
        return new Bullet();
    }
};


#endif //SHMUP_BULLET_H
