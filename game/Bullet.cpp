#include "Bullet.h"

void Bullet::load(std::unique_ptr<LoaderParams> pParams) {
    SDLGameObject::load(std::move(pParams));
    m_velocity = vec2(0, -5);
}

void Bullet::update() {
    SDLGameObject::update();
}

void Bullet::collided(const Collidable &collider) {

}
