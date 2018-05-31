#include "SDLGameObject.h"

#include <SDL.h>
#include "TextureManager.h"
#include "Game.h"

SDLGameObject::SDLGameObject(const LoaderParams *pParams) : GameObject(pParams) {
    m_position = Vector2D(pParams->getX(), pParams->getY());
    m_acceleration = Vector2D(0, 0);
    m_velocity = Vector2D(0, 0);

    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();

    m_currentRow = 0;
    m_currentFrame = 0;
}

void SDLGameObject::draw() {
    auto x = static_cast<int>(m_position.x);
    auto y = static_cast<int>(m_position.y);
    SDL_Renderer *renderer = Game::Instance()->getRenderer();

    TextureManager::Instance()->drawFrame(m_textureID, x, y, m_width, m_height, m_currentRow, m_currentFrame, renderer);
}

void SDLGameObject::update() {
    m_velocity += m_acceleration;
    m_position += m_velocity;
}

void SDLGameObject::clean() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}
