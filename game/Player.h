#ifndef SHMUP_PLAYER_H
#define SHMUP_PLAYER_H

#include "base/GameObjectFactory.h"
#include "sdl/SDLGameObject.h"

class Player : public SDLGameObject, public Collidable {
public:
    explicit Player(int id) : SDLGameObject(id) {}

    void update() override;

    void load(std::unique_ptr<LoaderParams> pParams) override;

    void collided(const Collidable &collider) override;

    const vec2 upperLeft() override { return m_position; }

    const vec2 lowerRight() override { return m_position + vec2(m_width, m_height); }
};

class PlayerCreator : public BaseCreator {
    GameObject *createGameObject(int id) const override {
        return new Player(id);
    }
};

#endif  // SHMUP_PLAYER_H
