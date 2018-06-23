#include "Player.h"

#include <SDL.h>
#include "Game.h"
#include "base/ServiceLocator.h"
#include "sdl/SDLInputHandler.h"

void Player::update() {
    Camera *pCamera = ServiceLocator::camera();

    auto cameraVelocity = pCamera->getVelocity();
    auto cameraPosition = pCamera->getPosition();
    m_velocity = cameraVelocity;

    InputHandler &handler = InputHandler::Instance();
    if (handler.isKeyDown(SDL_SCANCODE_RIGHT)) { m_velocity.x = 2; }
    if (handler.isKeyDown(SDL_SCANCODE_LEFT)) { m_velocity.x = -2; }
    if (handler.isKeyDown(SDL_SCANCODE_UP)) { m_velocity.y += -2; }
    if (handler.isKeyDown(SDL_SCANCODE_DOWN)) { m_velocity.y += 2; }

    if (handler.isKeyDown(SDL_SCANCODE_SPACE)) {
        ServiceLocator::bulletHandler()->playerShoots(static_cast<int>(m_position.x), static_cast<int>(m_position.y));
    }

    vec2 playerPosition = m_position + m_velocity;
    vec2 relativePlayerPosition = playerPosition - cameraPosition;
    vec2 screenDimensions = Game::Instance().windowSize();

    if (relativePlayerPosition.x >= 0 && relativePlayerPosition.x + m_width <= screenDimensions.x) {
        m_position.x = playerPosition.x;
    }

    if (relativePlayerPosition.y >= 0 && relativePlayerPosition.y + m_height <= screenDimensions.y) {
        m_position.y = playerPosition.y;
    } else {
        m_position.y += cameraVelocity.y;
    }
}

void Player::load(std::unique_ptr<LoaderParams> pParams) {
    SDLGameObject::load(std::move(pParams));
    m_numFrames = 3;
}

void Player::collided(const Collidable &collider) {

}
