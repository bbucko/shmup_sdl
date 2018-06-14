#include <base/GameObjectFactory.h>
#include <base/GameObject.h>
#include <sdl/SDLGameObject.h>
#include <sdl/SDLTextureManager.h>
#include "gmock/gmock.h"

namespace mocks {

    using ::testing::Return;
    using ::testing::StrictMock;
    using ::testing::NiceMock;
    using ::testing::Mock;
    using ::testing::_;

// @formatter:off
    class CollisionManagerMock : public CollisionManager {
    public:
        MOCK_METHOD1(checkCollisions, void(std::vector<GameObject *> objects));
    };

    class GameObjectFactoryMock : public GameObjectFactory {
    public:
        MOCK_METHOD2(create, GameObject *(int id, const std::string &typeID));
    };

    class CameraMock : public Camera {
    public:
        MOCK_METHOD0(getPosition, vec2());
    };

    class TextureManagerMock : public TextureManager {
    public:
        MOCK_METHOD2(load, bool(const std::string &fileName, const std::string &id));
        MOCK_METHOD1(clear, void(const std::string &id));

        MOCK_CONST_METHOD5(draw, void(const std::string &id, int x, int y, int width, int height));
        MOCK_CONST_METHOD7(draw, void(const std::string &id, int x, int y, int width, int height, int currentRow, int currentFrame));
        MOCK_CONST_METHOD9(draw, void(const std::string &id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame));
    };

    class FakeObject : public SDLGameObject {
    public:
        explicit FakeObject() : SDLGameObject(0) {}
    };

// @formatter:on

    class TestWithMocks : public testing::Test {
    protected:
        virtual void SetUp() {
            LOG_INFO("Creating Mocks");
            ServiceLocator::provide(std::make_unique<mocks::TextureManagerMock>());
            ServiceLocator::provide(std::make_unique<mocks::GameObjectFactoryMock>());
            ServiceLocator::provide(std::make_unique<mocks::CameraMock>());
            ServiceLocator::provide(std::make_unique<mocks::CollisionManagerMock>());

            LOG_INFO("Mocks created: " <<
                                       "gameObjectFactory: " << ServiceLocator::s_gameObjectFactory.get() <<
                                       " textureManager: " << ServiceLocator::s_textureManager.get() <<
                                       " camera: " << ServiceLocator::s_camera.get() <<
                                       " collisionManager: " << ServiceLocator::s_collisionManager.get());
        }

        virtual void TearDown() {
            LOG_INFO("TearDown: " <<
                                  "gameObjectFactory: " << ServiceLocator::s_gameObjectFactory.get() <<
                                  " textureManager: " << ServiceLocator::s_textureManager.get() <<
                                  " camera: " << ServiceLocator::s_camera.get() <<
                                  " collisionManager: " << ServiceLocator::s_collisionManager.get());

            ServiceLocator::s_gameObjectFactory = nullptr;
            ServiceLocator::s_textureManager = nullptr;
            ServiceLocator::s_bulletHandler = nullptr;
            ServiceLocator::s_camera = nullptr;
            ServiceLocator::s_collisionManager = nullptr;
        }


        mocks::TextureManagerMock *getManager() {
            TextureManager *pManager = ServiceLocator::textureManager();
            LOG_INFO("pManager: " << pManager);
            return dynamic_cast<mocks::TextureManagerMock *>(pManager);
        }

        mocks::CameraMock *getCamera() {
            Camera *pCamera = ServiceLocator::camera();
            LOG_INFO("pCamera: " << pCamera);
            return dynamic_cast<mocks::CameraMock *>(pCamera);
        }

        mocks::GameObjectFactoryMock *getFactory() {
            GameObjectFactory *pGameObjectFactory = ServiceLocator::gameObjectFactory();
            LOG_INFO("pGameObjectFactory: " << pGameObjectFactory);
            return dynamic_cast<mocks::GameObjectFactoryMock *>(pGameObjectFactory);
        }
    };
}

