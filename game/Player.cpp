#include "Player.h"

#include <SDL.h>

void Player::update() {
    m_currentFrame = int(((SDL_GetTicks() / 100) % 3));
}