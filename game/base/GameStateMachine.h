#ifndef SHMUP_GAMESTATEMACHINE_H
#define SHMUP_GAMESTATEMACHINE_H

#include "GameState.h"
#include <vector>

class GameStateMachine {
private:
    std::vector<GameState *> m_gameStates;

public:

    void pushState(GameState *pState);

    void changeState(GameState *pState);

    void popState();

    void update();

    void render();

    ~GameStateMachine() {
        for (auto gameState :m_gameStates) {
            delete gameState;
        }
    }
};


#endif //SHMUP_GAMESTATEMACHINE_H
