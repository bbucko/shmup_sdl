#include "Game.h"

#include <SDL_image.h>
#include <array>
#include <base/MenuState.h>
#include <base/InputHandler.h>
#include <base/PlayState.h>

#include "TextureManager.h"

void Game::update() {
    m_pGameStateMachine->update();
}

void Game::render() const {
    SDL_RenderClear(m_pRenderer);
    m_pGameStateMachine->render();
    SDL_RenderPresent(m_pRenderer);
}

void Game::terminate() {
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);

    IMG_Quit();
    SDL_Quit();
}

bool Game::running() const {
    return m_bRunning;
}

void Game::quit() {
    m_bRunning = false;
}

void Game::init() {
    if (!initSDL()) {
        LOG("Error occurred: " << SDL_GetError());
    }
    m_pGameStateMachine = new GameStateMachine();
    m_pGameStateMachine->changeState(new MenuState());

    m_bRunning = true;
}

bool Game::initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        LOG("SDL init success");

        if (IMG_Init(IMG_INIT_PNG) != 0) {
            LOG("SDL image success");

            m_pWindow = SDL_CreateWindow("SHMUP", 100, 100, 640, 480, SDL_WINDOW_RESIZABLE);
            if (m_pWindow != nullptr) {
                m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

                if (m_pRenderer != nullptr) {
                    LOG("SDL renderer success");
                    return true;
                }
            }
        }
    }
    return false;
}

void Game::handleEvents() {
    InputHandler::Instance().update();

    if (InputHandler::Instance().isKeyDown(SDL_SCANCODE_RETURN)) {
        m_pGameStateMachine->changeState(new PlayState());
    }

}
