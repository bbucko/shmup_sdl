#include "Player.h"

#include <SDL.h>
#include <base/InputHandler.h>

void Player::update() {
    m_currentFrame = int(((SDL_GetTicks() / 100) % 3));

    m_velocity.x = 0;
    m_velocity.y = 0;

    InputHandler &handler = InputHandler::Instance();
    if (handler.isKeyDown(SDL_SCANCODE_RIGHT)) {
        m_velocity.x = 2;
    }

    if (handler.isKeyDown(SDL_SCANCODE_LEFT)) {
        m_velocity.x = -2;
    }

    if (handler.isKeyDown(SDL_SCANCODE_UP)) {
        m_velocity.y = -2;
    }

    if (handler.isKeyDown(SDL_SCANCODE_DOWN)) {
        m_velocity.y = 2;
    }

    SDLGameObject::update();
}