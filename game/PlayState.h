#ifndef SHMUP_PLAYSTATE_H
#define SHMUP_PLAYSTATE_H

#include "base/GameState.h"
#include "base/GameObject.h"
#include <vector>
#include <sdl/SDLGameObject.h>

class PlayState : public GameState {
public:

    void update() override;

    void render() override;

    bool onEnter() override;

    bool onExit() override;

    std::string getStateID() const override { return s_playID; }

private:

    std::vector<GameObject *> m_objects;

    static const std::string s_playID;

    bool checkCollision(SDLGameObject *p1, SDLGameObject *p2);

    void calculateCollisions();
};

#endif //SHMUP_PLAYSTATE_H
