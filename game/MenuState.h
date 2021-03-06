#ifndef SHMUP_MENUSTATE_H
#define SHMUP_MENUSTATE_H

#include <MenuButton.h>
#include <vector>
#include "base/GameState.h"

class MenuState : public GameState {
public:
    bool onEnter() override;

    std::string getStateID() const override { return "MENU"; }
};

#endif  // SHMUP_MENUSTATE_H
