#ifndef SHMUP_GAME_H
#define SHMUP_GAME_H

#include "base/GameStateMachine.h"
#include "base/GameObject.h"
#include "base/Logger.h"

#include <vector>
#include <SDL.h>
#include <sdl/SDLGameObject.h>

class Game {
public:

    void init();

    void update();

    void render() const;

    bool running() const;

    void terminate();

    void quit();

    void handleEvents();

    vec2 getDimensions() const;

    SDL_Renderer *getRenderer() const { return m_pRenderer; }

    GameStateMachine *getStateMachine() const { return m_pGameStateMachine; }

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