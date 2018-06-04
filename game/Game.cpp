#include "Game.h"

#include <SDL_image.h>
#include <array>
#include <base/GameObjectFactory.h>
#include <base/BulletHandler.h>
#include "MenuState.h"
#include "sdl/InputHandler.h"
#include "PlayState.h"
#include "Player.h"
#include "Enemy.h"
#include "ServiceLocator.h"

void Game::update() {
    m_pGameStateMachine->update();
}

void Game::render() const {
    SDL_RenderClear(ServiceLocator::renderer());

    m_pGameStateMachine->render();

    SDL_RenderPresent(ServiceLocator::renderer());
}

void Game::terminate() {
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(ServiceLocator::renderer());

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
        LOG_INFO("Error occurred: " << SDL_GetError());
    }

    ServiceLocator::provide(new BulletHandler());
    ServiceLocator::provide(new TextureManager());
    ServiceLocator::provide(new GameObjectFactory());

    ServiceLocator::gameObjectFactory()->registerType("MenuButton", new MenuButtonCreator());
    ServiceLocator::gameObjectFactory()->registerType("Player", new PlayerCreator());
    ServiceLocator::gameObjectFactory()->registerType("Enemy", new EnemyCreator());

    m_pGameStateMachine = new GameStateMachine();
    m_pGameStateMachine->changeState(new MenuState());

    m_bRunning = true;
}

bool Game::initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        LOG_INFO("SDL init success");

        if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != 0) {
            LOG_INFO("SDL image success");

            m_pWindow = SDL_CreateWindow("SHMUP", 100, 100, 640, 480, SDL_WINDOW_RESIZABLE);
            if (m_pWindow != nullptr) {
                auto m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

                if (m_pRenderer != nullptr) {
                    LOG_INFO("SDL renderer success");
                    ServiceLocator::provide(m_pRenderer);
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

vec2 Game::getDimensions() const {
    int width;
    int height;
    SDL_GetWindowSize(m_pWindow, &width, &height);
    return vec2(width, height);
}
