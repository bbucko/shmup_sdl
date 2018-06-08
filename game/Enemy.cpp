#include "Enemy.h"
#include "Game.h"
#include "ServiceLocator.h"

void Enemy::draw() {
    auto x = static_cast<int>(m_position.x);
    auto y = static_cast<int>(m_position.y);

    ServiceLocator::textureManager()->draw(m_textureID, x, y, m_width, m_height, ServiceLocator::renderer());
}

void Enemy::update() {
    if (m_position.x <= 0) {
        m_velocity.x = 1;
    }

    if (m_position.x + m_width >= Game::Instance().getDimensions().y) {
        m_velocity.x = -1;
    }

    SDLGameObject::update();
}

void Enemy::load(std::unique_ptr<LoaderParams> const &pParams) {
    SDLGameObject::load(pParams);
    m_velocity = vec2(1, 0);
}