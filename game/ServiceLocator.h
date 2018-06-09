#ifndef SHMUP_SERVICELOCATOR_H
#define SHMUP_SERVICELOCATOR_H

#include <base/GameObjectFactory.h>
#include "Game.h"
#include "TextureManager.h"
#include "base/BulletHandler.h"

class ServiceLocator {
public:
    static BulletHandler *bulletHandler();

    static TextureManager *textureManager();

    static GameObjectFactory *gameObjectFactory();

    static Renderer *renderer();

    static void provide(std::unique_ptr<BulletHandler> bulletHandler);

    static void provide(std::unique_ptr<TextureManager> textureManager);

    static void provide(std::unique_ptr<GameObjectFactory> gameObjectFactory);

    static void provide(Renderer *gameObjectFactory);

    static void clear() {
        m_gameObjectFactory = nullptr;
        m_textureManager = nullptr;
        m_bulletHandler = nullptr;
    }
private:
    static std::unique_ptr<BulletHandler> m_bulletHandler;
    static std::unique_ptr<TextureManager> m_textureManager;
    static std::unique_ptr<GameObjectFactory> m_gameObjectFactory;
    static Renderer *m_renderer;

    ServiceLocator() = default;

    ~ServiceLocator() = default;
};

#endif  // SHMUP_SERVICELOCATOR_H
