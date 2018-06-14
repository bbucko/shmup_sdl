#ifndef SHMUP_GAMESTATEMACHINE_H
#define SHMUP_GAMESTATEMACHINE_H

#include <vector>
#include <utils/Logger.h>
#include <utils/Memory.h>
#include "GameState.h"

class GameStateMachine {
private:
    std::vector<GameState *> m_gameStates;

public:
    void pushState(GameState *pState);

    void changeState(GameState *pState);

    void popState();

    void update();

    void render();

    ~GameStateMachine() { DELETE_VECTOR(m_gameStates); }
};

#endif  // SHMUP_GAMESTATEMACHINE_H
