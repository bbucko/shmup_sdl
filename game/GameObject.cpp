#include "GameObject.h"
#include <utility>

void GameObject::load(int x, int y, int width, int height, std::string textureID) {
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
    m_textureID = std::move(textureID);

    m_currentRow = 1;
    m_currentFrame = 0;
}

void GameObject::draw(SDL_Renderer *pRenderer) {
    TextureManager::Instance()->drawFrame(m_textureID, m_x, m_y, m_width, m_height, m_currentRow, m_currentFrame, pRenderer);
}
