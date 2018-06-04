#ifndef SHMUP_SERVICELOCATOR_H
#define SHMUP_SERVICELOCATOR_H

#include <base/GameObjectFactory.h>
#include "base/BulletHandler.h"
#include "TextureManager.h"


class ServiceLocator {

public:
    static BulletHandler *bulletHandler();

    static TextureManager *textureManager();

    static GameObjectFactory *gameObjectFactory();

    static void provide(BulletHandler *bulletHandler);

    static void provide(TextureManager *textureManager);

    static void provide(GameObjectFactory *gameObjectFactory);

private:
    static BulletHandler *m_bulletHandler;
    static TextureManager *m_textureManager;
    static GameObjectFactory *m_gameObjectFactory;

    ServiceLocator() = default;

    ~ServiceLocator() = default;
};


#endif //SHMUP_SERVICELOCATOR_H
