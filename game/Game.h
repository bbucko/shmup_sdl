#ifndef SHMUP_GAME_H
#define SHMUP_GAME_H

#include "base/GameStateMachine.h"
#include "base/GameObject.h"
#include "utils/Logger.h"

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

    GameStateMachine *getStateMachine() const { return m_pGameStateMachine; }

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


#endif //SHMUP_GAME_H