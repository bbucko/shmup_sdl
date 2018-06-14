#ifndef SHMUP_GAME_H
#define SHMUP_GAME_H

#include <SDL.h>
#include <vector>
#include <utils/Logger.h>
#include <base/GameObject.h>
#include <base/GameStateMachine.h>
#include <sdl/SDLGameObject.h>

class Game {
public:
    void init();

    void terminate();

    void update() const;

    void render() const;

    void handleEvents() const;

    inline bool running() const { return m_bRunning; }

    inline void quit() { m_bRunning = false; };

    inline SDL_Renderer *renderer() const { return m_pRenderer; }

    vec2 windowSize() const;

    static Game &Instance() {
        static Game instance;
        return instance;
    };

private:
    Game() = default;

    ~Game() = default;

    bool initSDL();

    bool m_bRunning{false};

    SDL_Window *m_pWindow{nullptr};

    SDL_Renderer *m_pRenderer{nullptr};

    std::unique_ptr<GameStateMachine> m_pGameStateMachine;
};

#endif  // SHMUP_GAME_H