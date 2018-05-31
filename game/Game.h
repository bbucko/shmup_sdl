#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <array>
#include <vector>

#include "TextureManager.h"
#include "GameObject.h"

#ifndef MOLTENVKCPP_GAME_H
#define MOLTENVKCPP_GAME_H

class Game {
private:
    SDL_Window *m_pWindow;
    SDL_Renderer *m_pRenderer;

    std::vector<GameObject *> objects;

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
