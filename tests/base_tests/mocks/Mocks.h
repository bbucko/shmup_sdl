#include <base/GameObjectFactory.h>
#include <base/GameObject.h>
#include <TextureManager.h>
#include <sdl/SDLGameObject.h>
#include "gmock/gmock.h"

namespace mocks {

    using ::testing::Return;
    using ::testing::NiceMock;
    using ::testing::Mock;
    using ::testing::_;

// @formatter:off
    class GameObjectFactoryMock : public GameObjectFactory {
    public:
        MOCK_METHOD1(create, GameObject *(std::string typeID));

    };

    class CameraMock : public Camera {
    public:
        MOCK_METHOD0(getPosition, vec2());

    };

    class TextureManagerMock : public TextureManager {
    public:
        MOCK_METHOD3(load, bool(const std::string &fileName, std::string id, Renderer *pRenderer));
        MOCK_METHOD10(drawTile, void(const std::string &id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, Renderer *pRenderer));
    };

    class FakeObject : public SDLGameObject {
    };

// @formatter:on
    class TestWithMocks : public testing::Test {
    protected:
        virtual void SetUp() {
            LOG_INFO("CreatingMocks");
            ServiceLocator::provide(std::make_unique<NiceMock<mocks::TextureManagerMock>>());
            ServiceLocator::provide(std::make_unique<NiceMock<mocks::GameObjectFactoryMock>>());
            ServiceLocator::provide(std::make_unique<NiceMock<mocks::CameraMock>>());
        }

        virtual void TearDown() {
            LOG_INFO("TearDown: gameObjectFactory: " << ServiceLocator::s_gameObjectFactory.get() <<
                                                     " textureManager: " << ServiceLocator::s_textureManager.get() <<
                                                     " camera: " << ServiceLocator::s_camera.get());
            ServiceLocator::s_gameObjectFactory = nullptr;
            ServiceLocator::s_textureManager = nullptr;
            ServiceLocator::s_bulletHandler = nullptr;
            ServiceLocator::s_camera = nullptr;
        }


        NiceMock<mocks::TextureManagerMock> *getManager() {
            TextureManager *pManager = ServiceLocator::textureManager();
            LOG_INFO("pManager: " << pManager);
            return dynamic_cast<NiceMock<mocks::TextureManagerMock> *>(pManager);
        }

        NiceMock<mocks::CameraMock> *getCamera() {
            Camera *pCamera = ServiceLocator::camera();
            LOG_INFO("pCamera: " << pCamera);
            return dynamic_cast<NiceMock<mocks::CameraMock> *>(pCamera);
        }

        NiceMock<mocks::GameObjectFactoryMock> *getFactory() {
            GameObjectFactory *pGameObjectFactory = ServiceLocator::gameObjectFactory();
            LOG_INFO("pGameObjectFactory: " << pGameObjectFactory);
            return dynamic_cast<NiceMock<mocks::GameObjectFactoryMock> *>(pGameObjectFactory);
        }
    };
}

