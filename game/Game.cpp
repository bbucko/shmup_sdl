#include <SDL.h>
#include <SDL_image.h>
#include "MenuState.h"
#include "PlayState.h"
#include "Player.h"
#include "Enemy.h"
#include <base/BulletHandler.h>
#include <base/ServiceLocator.h>
#include <sdl/SDLInputHandler.h>
#include <sdl/SDLTextureManager.h>

void Game::update() const {
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

void Game::init() {
    if (!initSDL()) {
        LOG_INFO("Error occurred: " << SDL_GetError());
    }

    ServiceLocator::provide(std::make_unique<BulletHandler>());
    ServiceLocator::provide(std::make_unique<SDLTextureManager>(m_pRenderer));
    ServiceLocator::provide(std::make_unique<GameObjectFactory>());
    ServiceLocator::provide(std::make_unique<Camera>());
    ServiceLocator::provide(std::make_unique<CollisionManager>());

    ServiceLocator::gameObjectFactory()->registerType("MenuButton", new MenuButtonCreator());
    ServiceLocator::gameObjectFactory()->registerType("Player", new PlayerCreator());
    ServiceLocator::gameObjectFactory()->registerType("Enemy", new EnemyCreator());

    m_pGameStateMachine = std::make_unique<GameStateMachine>();
//    m_pGameStateMachine->changeState(new MenuState());
    m_pGameStateMachine->changeState(new PlayState());

    m_bRunning = true;
}

bool Game::initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        LOG_INFO("SDL init success");

        if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != 0) {
            LOG_INFO("SDL_Image init success");

            m_pWindow = SDL_CreateWindow("SHMUP", 100, 100, 640, 480, SDL_WINDOW_RESIZABLE);
            if (m_pWindow != nullptr) {
                m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

                if (m_pRenderer != nullptr) {
                    LOG_INFO("SDL Renderer init success");
                    return true;
                }
            }
        }
    }
    return false;
}

void Game::handleEvents() const {
    InputHandler::Instance().update();

    if (InputHandler::Instance().isKeyDown(SDL_SCANCODE_RETURN)) {
        m_pGameStateMachine->changeState(new PlayState());
    }

}

vec2 Game::windowSize() const {
    if (m_pWindow == nullptr) return vec2(640, 480);

    int width, height;
    SDL_GetWindowSize(m_pWindow, &width, &height);
    return vec2(width, height);
}
