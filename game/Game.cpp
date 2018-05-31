#include "Game.h"

#include <SDL_image.h>
#include <array>

#include "TextureManager.h"
#include "Player.h"
#include "Enemy.h"

void Game::render() {
    std::cout << "Frame #" << m_iFrames << std::endl;
    SDL_RenderClear(m_pRenderer);

    for (auto object : objects) {
        object->draw();
    }

    SDL_RenderPresent(m_pRenderer);
}

void Game::terminate() {
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);

    IMG_Quit();

    SDL_Quit();
    std::cout << "Frames rendered: " << m_iFrames << std::endl;
}

bool Game::running() {
    return m_bRunning;
}

void Game::handleEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                m_bRunning = false;
                break;

            default:
                break;
        }
    }
}

void Game::update() {
    std::cout << "Ticks: " << SDL_GetTicks() << std::endl;

    m_iFrames++;

    for (auto object : objects) {
        object->update();
    }
}

void Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        std::cout << "SDL init success" << std::endl;

        if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0) {
            std::cout << "SDL image success" << std::endl;

            m_pWindow = SDL_CreateWindow("SHMUP", 100, 100, 640, 480, SDL_WINDOW_RESIZABLE);
            if (m_pWindow != nullptr) {
                m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

                if (m_pRenderer != nullptr) {
                    std::cout << "SDL renderer success" << std::endl;
                    SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);

                    TextureManager::Instance()->load("res/plane.png", "plane", m_pRenderer);
                    TextureManager::Instance()->load("res/plane1.png", "plane1", m_pRenderer);

                    objects.push_back(new Player(new LoaderParams(0, 0, 65, 65, "plane")));
                    objects.push_back(new Enemy(new LoaderParams(130, 130, 65, 65, "plane1")));

                    m_bRunning = true;
                    std::cout << "Main loop running" << std::endl;
                    return;
                }
            }
        }
    }

    std::cout << "Error occurred: " << SDL_GetError() << std::endl;
}

SDL_Renderer *Game::getRenderer() {
    return m_pRenderer;
}

static Game *s_pInstance = nullptr;

Game *Game::Instance() {
    if (s_pInstance == nullptr) {
        s_pInstance = new Game();
        return s_pInstance;
    }

    return s_pInstance;
}
