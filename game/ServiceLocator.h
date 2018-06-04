#ifndef SHMUP_SERVICELOCATOR_H
#define SHMUP_SERVICELOCATOR_H

#include <base/GameObjectFactory.h>
#include "base/BulletHandler.h"
#include "TextureManager.h"

typedef SDL_Renderer Renderer;

class ServiceLocator {

public:
    static BulletHandler *bulletHandler();

    static TextureManager *textureManager();

    static GameObjectFactory *gameObjectFactory();

    static Renderer *renderer();

    static void provide(BulletHandler *bulletHandler);

    static void provide(TextureManager *textureManager);

    static void provide(GameObjectFactory *gameObjectFactory);

    static void provide(Renderer *gameObjectFactory);

private:
    static BulletHandler *m_bulletHandler;
    static TextureManager *m_textureManager;
    static GameObjectFactory *m_gameObjectFactory;
    static Renderer *m_renderer;

    ServiceLocator() = default;

    ~ServiceLocator() = default;
};


#endif //SHMUP_SERVICELOCATOR_H
