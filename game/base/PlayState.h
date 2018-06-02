#ifndef SHMUP_PLAYSTATE_H
#define SHMUP_PLAYSTATE_H

#include "GameState.h"
#include "GameObject.h"
#include <vector>

class PlayState : public GameState {
public:

    void update() override;

    void render() override;

    bool onEnter() override;

    bool onExit() override;

    std::string getStateID() const override { return s_playID; }

private:

    std::vector<GameObject *> objects;

    static const std::string s_playID;
};

#endif //SHMUP_PLAYSTATE_H
