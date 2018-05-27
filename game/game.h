#include <iostream>
#include <SDL_system.h>

#ifndef MOLTENVKCPP_GAME_H
#define MOLTENVKCPP_GAME_H

class Game {
private:
    SDL_Window *m_pWindow;
    SDL_Renderer *m_pRenderer;

    SDL_Texture *pTexture;

    SDL_Rect m_sourceRectangle;
    SDL_Rect m_destinationRectangle;

    bool m_bRunning;
    int m_iFrames = 0;
public:

    Game();

    void update();

    void handleEvents();

    void render();

    void terminate();

    bool running();
};


#endif //MOLTENVKCPP_GAME_H
