#include <iostream>
#include <SDL_system.h>
#include "TextureManager.h"

#ifndef MOLTENVKCPP_GAME_H
#define MOLTENVKCPP_GAME_H

class Game {
private:
    SDL_Window *m_pWindow;
    SDL_Renderer *m_pRenderer;

    TextureManager *m_pTextureManager;

    bool m_bRunning;
    int m_iFrames = 0;
public:

    Game();

    void update();

    void handleEvents();

    void render();

    void terminate();

    bool running();

    void init();
};


#endif //MOLTENVKCPP_GAME_H
