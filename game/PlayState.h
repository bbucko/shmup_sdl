#ifndef SHMUP_PLAYSTATE_H
#define SHMUP_PLAYSTATE_H

#include <base/Level.h>
#include <sdl/SDLGameObject.h>
#include "base/GameObject.h"
#include "base/GameState.h"

class PlayState : public GameState {
public:
    void update() override;

    void render() override;

    bool onEnter() override;

    std::string getStateID() const override { return "PLAY"; }

private:
    bool checkCollision(SDLGameObject *p1, SDLGameObject *p2);

    void calculateCollisions();

    Level *pLevel;
};

#endif  // SHMUP_PLAYSTATE_H
