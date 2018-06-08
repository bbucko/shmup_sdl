#ifndef SHMUP_GAME_H
#define SHMUP_GAME_H

#include "base/GameObject.h"
#include "base/GameStateMachine.h"
#include "utils/Logger.h"

#include <SDL.h>
#include <sdl/SDLGameObject.h>
#include <vector>

typedef SDL_Renderer Renderer;

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

    static Game &Instance() {
        static Game instance;
        return instance;
    };

private:
    SDL_Window *m_pWindow;

    GameStateMachine *m_pGameStateMachine;

    bool m_bRunning;

    Game() = default;

    ~Game() {
        delete m_pGameStateMachine;
    };

    bool initSDL();
};

#endif  // SHMUP_GAME_H