#ifndef SHMUP_BULLET_H
#define SHMUP_BULLET_H

#include <base/GameObjectFactory.h>
#include "sdl/SDLGameObject.h"

class Bullet : public SDLGameObject, public Collidable {
public:
    explicit Bullet(int id) : SDLGameObject(id) {}

    void load(std::unique_ptr<LoaderParams> pParams) override;

    void update() override;

    void collided(const Collidable &collider) override;

    const vec2 upperLeft() override { return m_position; }

    const vec2 lowerRight() override { return m_position + vec2(m_width, m_height); }
};

class BulletCreator : public BaseCreator {
    GameObject *createGameObject(int id) const override {
        return new Bullet(id);
    }
};

#endif  // SHMUP_BULLET_H
