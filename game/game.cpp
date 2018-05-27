
#include <SDL.h>
#include <SDL_image.h>
#include "game.h"

void Game::render() {
    std::cout << "Frame #" << m_iFrames << std::endl;
    SDL_RenderClear(m_pRenderer);

    SDL_RenderCopy(m_pRenderer, pTexture, &m_sourceRectangle, &m_destinationRectangle);

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
    m_iFrames++;

}

Game::Game() {
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        std::cout << "SDL init success" << std::endl;

        if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0) {
            std::cout << "SDL image success" << std::endl;

            m_pWindow = SDL_CreateWindow("SHMUP", 100, 100, 640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_INPUT_FOCUS);
            if (m_pWindow != nullptr) {
                m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
                std::cout << "SDL renderer success" << std::endl;
                if (m_pRenderer != nullptr) {
                    SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
                    SDL_SetRenderDrawBlendMode(m_pRenderer, SDL_BLENDMODE_BLEND);

                    SDL_Surface *pSurface = IMG_Load("res/shooter/1945.png");
                    pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pSurface);
                    SDL_FreeSurface(pSurface);

                    SDL_QueryTexture(pTexture, nullptr, nullptr, &m_sourceRectangle.w, &m_sourceRectangle.h);

                    m_destinationRectangle.x = m_sourceRectangle.x = 0;
                    m_destinationRectangle.y = m_sourceRectangle.y = 0;
                    m_destinationRectangle.w = m_sourceRectangle.w;
                    m_destinationRectangle.h = m_sourceRectangle.h;

                    m_bRunning = true;
                    std::cout << "Main loop running" << std::endl;
                    return;
                }
            }
        }
    }

    std::cout << "Error occurred: " << SDL_GetError() << std::endl;
}
