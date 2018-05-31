#ifndef SHMUP_GAME_H
#define SHMUP_GAME_H

#include <vector>
#include <SDL.h>
#include "base/GameObject.h"

class Game {
public:

    void init();

    void update();

    void render() const;

    bool running() const;

    void terminate();

    void quit();

    SDL_Renderer *getRenderer() const {
        return m_pRenderer;
    }

    static Game &Instance() {
        static Game instance;
        return instance;
    };

private:
    SDL_Window *m_pWindow;

    SDL_Renderer *m_pRenderer;

    std::vector<GameObject *> objects;

    bool m_bRunning;

    int m_iFrames = 0;

    Game() = default;

    ~Game() = default;

    void loadTextures();

    void initPlayer();

    bool initSDL();

    void initObjects();
};


#endif //SHMUP_GAME_H