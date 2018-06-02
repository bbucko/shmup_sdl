#include "Enemy.h"
#include "TextureManager.h"
#include "Game.h"

void Enemy::draw() {
    auto x = static_cast<int>(m_position.x);
    auto y = static_cast<int>(m_position.y);

    TextureManager::Instance().draw(m_textureID, x, y, m_width, m_height, Game::Instance().getRenderer());
}

void Enemy::update() {
    if (m_position.x <= 0) {
        m_velocity.x = 1;
    }

    if (m_position.x + m_width >= 640) {
        m_velocity.x = -1;
    }

    SDLGameObject::update();

}
