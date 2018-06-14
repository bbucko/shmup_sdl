#ifndef SHMUP_GAMESTATE_H
#define SHMUP_GAMESTATE_H

#include <string>
#include <vector>

#include "GameObject.h"

class GameState {
public:
    virtual void update();

    virtual void render();

    virtual bool onEnter();

    virtual bool onExit();

    virtual std::string getStateID() const = 0;

    virtual ~GameState();

protected:
    std::vector<GameObject *> m_objects;

    std::vector<std::string> m_textureIds;
};

#endif  // SHMUP_GAMESTATE_H
