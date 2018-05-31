#ifndef SHMUP_GAME_H
#define SHMUP_GAME_H

#include <vector>
#include <SDL.h>
#include "base/GameObject.h"

class Game {
private:
    SDL_Window *m_pWindow;
    SDL_Renderer *m_pRenderer;

    std::vector<GameObject *> objects;

    bool m_bRunning;
    int m_iFrames = 0;

    Game() = default;

public:

    void update();

    void handleEvents();

    void render();

    void terminate();

    bool running();

    void init();

    SDL_Renderer *getRenderer();

    static Game *Instance();
};


#endif //SHMUP_GAME_H
