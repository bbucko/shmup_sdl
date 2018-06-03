#include <Bullet.h>
#include "BulletHandler.h"
#include "Logger.h"

void BulletHandler::playerShoots(int x, int y) {
    LOG_INFO("player shhots: " << x << " :: " << y);
    auto *bullet = new Bullet();
    bullet->load(new LoaderParams(x + 16, y - 16, 32, 32, "bullet"));
    bullets.push_back(bullet);
}

void BulletHandler::enemyShoots(int x, int y) {
    LOG_INFO("enemy shhots: " << x << " :: " << y);
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
            delete *i;
            i = bullets.erase(i);
        } else {
            (*i)->update();
            ++i;
        }
    }
}
