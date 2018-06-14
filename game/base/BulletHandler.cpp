#include "utils/Logger.h"
#include <Game.h>
#include <base/ServiceLocator.h>
#include "Bullet.h"

void BulletHandler::playerShoots(int x, int y) {
    LOG_INFO("player shots: " << x << " :: " << y);

    auto now = std::chrono::system_clock::now();
    const std::chrono::duration<double, std::milli> &timeSinceLastShot = now - m_lastPlayerShootAt;
    if (timeSinceLastShot.count() > 200) {
        auto bullet = new Bullet(static_cast<int>(m_bullets.size()));
        bullet->load(std::make_unique<LoaderParams>(x + 16, y - 16, 32, 32, 1, "bullet"));

        m_bullets.push_back(bullet);

        m_lastPlayerShootAt = std::chrono::system_clock::now();
    }
}

void BulletHandler::enemyShoots(int x, int y) {
    LOG_INFO("enemy shots: " << x << " :: " << y);
}

void BulletHandler::render() const {
    for (auto bullet : m_bullets) {
        bullet->draw();
    }
}

void BulletHandler::update() {
    auto cameraPosition = ServiceLocator::camera()->getPosition();

    auto i = std::begin(m_bullets);
    while (i != std::end(m_bullets)) {
        auto *bullet = dynamic_cast<SDLGameObject *>(*i);
        if (bullet->getPosition().y - cameraPosition.y < 0) {
            bullet->clean();
            delete bullet;
            i = m_bullets.erase(i);
        } else {
            (*i)->update();
            ++i;
        }
    }
}
