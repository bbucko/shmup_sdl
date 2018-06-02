#include "Bullet.h"

void Bullet::load(const LoaderParams *pParams) {
    SDLGameObject::load(pParams);
    m_velocity = vec2(0, -5);
}

void Bullet::update() {
    SDLGameObject::update();
}
