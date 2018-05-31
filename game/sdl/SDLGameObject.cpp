#include "SDLGameObject.h"

#include <SDL.h>
#include "TextureManager.h"
#include "Game.h"

SDLGameObject::SDLGameObject(const LoaderParams *pParams) : GameObject(pParams) {
    m_position = glm::vec2(pParams->getX(), pParams->getY());
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();

    m_currentRow = 0;
    m_currentFrame = 0;
}

void SDLGameObject::draw() {
    int x = static_cast<int>(m_position.x);
    int y = static_cast<int>(m_position.y);
    SDL_Renderer *renderer = Game::Instance()->getRenderer();

    TextureManager::Instance()->drawFrame(m_textureID, x, y, m_width, m_height, m_currentRow, m_currentFrame, renderer);
}

void SDLGameObject::update() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void SDLGameObject::clean() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}
