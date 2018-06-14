#ifndef SHMUP_SERVICELOCATOR_H
#define SHMUP_SERVICELOCATOR_H

#include "Game.h"

#include <base/GameObjectFactory.h>
#include <base/TextureManager.h>
#include <base/Camera.h>
#include <base/CollisionManager.h>
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

    static CollisionManager *collisionManager();

    static GameObjectFactory *gameObjectFactory();

    static Camera *camera();

    static void provide(std::unique_ptr<BulletHandler> bulletHandler);

    static void provide(std::unique_ptr<TextureManager> textureManager);

    static void provide(std::unique_ptr<GameObjectFactory> gameObjectFactory);

    static void provide(std::unique_ptr<Camera> camera);

    static void provide(std::unique_ptr<CollisionManager> collisionManager);

private:
    static std::unique_ptr<BulletHandler> s_bulletHandler;
    static std::unique_ptr<TextureManager> s_textureManager;
    static std::unique_ptr<GameObjectFactory> s_gameObjectFactory;
    static std::unique_ptr<Camera> s_camera;
    static std::unique_ptr<CollisionManager> s_collisionManager;

    ServiceLocator() = default;

    ~ServiceLocator() = default;

#ifdef INCLUDE_MOCKS
    friend mocks::TestWithMocks;

    static void clear() {
        ServiceLocator::s_bulletHandler.release();
        ServiceLocator::s_textureManager.release();
        ServiceLocator::s_gameObjectFactory.release();
        ServiceLocator::s_camera.release();
        ServiceLocator::s_collisionManager.release();
    }
#endif

};

#endif  // SHMUP_SERVICELOCATOR_H
