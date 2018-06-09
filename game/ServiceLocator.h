#ifndef SHMUP_SERVICELOCATOR_H
#define SHMUP_SERVICELOCATOR_H

#include <base/GameObjectFactory.h>
#include "Game.h"
#include "TextureManager.h"
#include "base/BulletHandler.h"

#ifdef INCLUDE_MOCKS
namespace mocks {
    class TestWithMocks;
}
#endif

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


private:
    static std::unique_ptr<BulletHandler> m_bulletHandler;
    static std::unique_ptr<TextureManager> m_textureManager;
    static std::unique_ptr<GameObjectFactory> m_gameObjectFactory;
    static Renderer *m_renderer;

    ServiceLocator() = default;

    ~ServiceLocator() = default;

#ifdef INCLUDE_MOCKS
    friend mocks::TestWithMocks;
#endif

};

#endif  // SHMUP_SERVICELOCATOR_H
