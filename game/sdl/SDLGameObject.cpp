#include "SDLGameObject.h"

#include <SDL.h>
#include "TextureManager.h"
#include "Game.h"

SDLGameObject::SDLGameObject(const LoaderParams *pParams) : GameObject(pParams) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    m_x = pParams->getX();
    m_y = pParams->getY();
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();

    m_currentRow = 0;
    m_currentFrame = 0;
}

void SDLGameObject::draw() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;

    SDL_Renderer *renderer = Game::Instance()->getRenderer();
    TextureManager::Instance()->drawFrame(m_textureID, m_x, m_y, m_width, m_height, m_currentRow, m_currentFrame, renderer);
}

void SDLGameObject::update() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void SDLGameObject::clean() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}
