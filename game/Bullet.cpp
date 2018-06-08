#include "Bullet.h"

void Bullet::load(std::unique_ptr<LoaderParams> const &pParams) {
    SDLGameObject::load(pParams);
    m_velocity = vec2(0, -5);
}

void Bullet::update() {
    SDLGameObject::update();
}
