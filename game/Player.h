#ifndef SHMUP_PLAYER_H
#define SHMUP_PLAYER_H

#include "base/GameObjectFactory.h"
#include "sdl/SDLGameObject.h"

class Player : public SDLGameObject {
public:
    explicit Player(int id) : SDLGameObject(id) {}

    void update() override;

    void load(std::unique_ptr<LoaderParams> pParams) override;
};

class PlayerCreator : public BaseCreator {
    GameObject *createGameObject(int id) const override {
        return new Player(id);
    }
};

#endif  // SHMUP_PLAYER_H
