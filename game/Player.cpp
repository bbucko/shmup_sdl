#include "Player.h"

#include <SDL.h>
#include "Game.h"
#include "ServiceLocator.h"
#include "sdl/InputHandler.h"

void Player::update() {
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

    if (handler.isKeyDown(SDL_SCANCODE_SPACE)) {
        ServiceLocator::bulletHandler()->playerShoots(static_cast<int>(m_position.x), static_cast<int>(m_position.y));
    }

    vec2 updatedPosition = m_position + m_velocity;

    if (updatedPosition.x >= 0 && updatedPosition.x + m_width <= Game::Instance().getDimensions().x) {
        m_position.x = updatedPosition.x;
    }

    if (updatedPosition.y >= 0 && updatedPosition.y + m_height <= Game::Instance().getDimensions().y) {
        m_position.y = updatedPosition.y;
    }
}

void Player::load(std::unique_ptr<LoaderParams> const &pParams) {
    SDLGameObject::load(pParams);
    m_numFrames = 3;
}
