#ifndef SHMUP_MENUSTATE_H
#define SHMUP_MENUSTATE_H

#include <MenuButton.h>
#include "GameState.h"

class MenuState : public GameState {
public:

    void update() override;

    void render() override;

    bool onEnter() override;

    bool onExit() override;

    std::string getStateID() const override { return s_menuID; }

private:

    MenuButton *m_playBtn;
    MenuButton *m_exitBtn;

    static const std::string s_menuID;
};

#endif //SHMUP_MENUSTATE_H
