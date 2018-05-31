#include "Player.h"

#include <SDL.h>

void Player::update() {
    m_currentFrame = int(((SDL_GetTicks() / 100) % 3));
    m_position = m_position + glm::vec2(1, 1);
}