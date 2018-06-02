#ifndef SHMUP_GAME_H
#define SHMUP_GAME_H

#include "base/GameStateMachine.h"
#include "base/GameObject.h"
#include "base/Logger.h"

#include <vector>
#include <SDL.h>

class Game {
public:

    void init();

    void update();

    void render() const;

    bool running() const;

    void terminate();

    void quit();

    void handleEvents();

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

    GameStateMachine *m_pGameStateMachine;

    bool m_bRunning;

    Game() = default;

    ~Game() = default;

    bool initSDL();
};


#endif //SHMUP_GAME_H