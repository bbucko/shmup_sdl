#include "Enemy.h"
#include "Game.h"

void Enemy::draw() {
    SDLGameObject::draw();
}

void Enemy::update() {
    if (m_position.x <= 0) {
        m_velocity.x = 1;
    }

    if (m_position.x + m_width >= Game::Instance().windowSize().y) {
        m_velocity.x = -1;
    }

    SDLGameObject::update();
}

void Enemy::load(std::unique_ptr<LoaderParams> pParams) {
    SDLGameObject::load(std::move(pParams));
    m_velocity = vec2(1, 0);
}
