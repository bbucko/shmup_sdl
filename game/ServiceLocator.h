#ifndef SHMUP_SERVICELOCATOR_H
#define SHMUP_SERVICELOCATOR_H

#include <base/GameObjectFactory.h>
#include <base/Camera.h>
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

    static Camera *camera();

    static void provide(std::unique_ptr<BulletHandler> bulletHandler);

    static void provide(std::unique_ptr<TextureManager> textureManager);

    static void provide(std::unique_ptr<GameObjectFactory> gameObjectFactory);

    static void provide(std::unique_ptr<Camera> camera);

    static void provide(Renderer *gameObjectFactory);

private:
    static std::unique_ptr<BulletHandler> s_bulletHandler;
    static std::unique_ptr<TextureManager> s_textureManager;
    static std::unique_ptr<GameObjectFactory> s_gameObjectFactory;
    static std::unique_ptr<Camera> s_camera;
    static Renderer *s_renderer;

    ServiceLocator() = default;

    ~ServiceLocator() = default;

#ifdef INCLUDE_MOCKS
    friend mocks::TestWithMocks;
#endif

};

#endif  // SHMUP_SERVICELOCATOR_H
