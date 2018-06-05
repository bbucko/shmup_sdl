#include <memory>
#include "Bullet.h"
#include "BulletHandler.h"
#include "utils/Logger.h"

void BulletHandler::playerShoots(int x, int y) {
    auto now = std::chrono::system_clock::now();
    const std::chrono::duration<double, std::milli> &timeSinceLastShot = now - m_lastPlayerShootAt;
    if (timeSinceLastShot.count() > 200) {
        auto loaderParams = std::make_shared<LoaderParams>(x + 16, y - 16, 32, 32, 1, "bullet");
        auto bullet = new Bullet();
        bullet->load(loaderParams.get());
        bullets.push_back(bullet);

        m_lastPlayerShootAt = std::chrono::system_clock::now();
    }
}

void BulletHandler::enemyShoots(int x, int y) {
    LOG_INFO("enemy shots: " << x << " :: " << y);
}

void BulletHandler::render() {
    for (auto bullet : bullets) {
        bullet->draw();
    }
}

void BulletHandler::update() {
    auto i = std::begin(bullets);
    while (i != std::end(bullets)) {
        auto *bullet = dynamic_cast<SDLGameObject *>(*i);
        if (bullet->getPosition().y <= 0) {
            bullet->clean();
            delete bullet;
            i = bullets.erase(i);
        } else {
            (*i)->update();
            ++i;
        }
    }
}

BulletHandler::~BulletHandler() {
    for (auto bullet : bullets) {
        delete bullet;
    }
}
