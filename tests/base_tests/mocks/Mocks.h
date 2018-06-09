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

    class TextureManagerMock : public TextureManager {
    public:
        MOCK_METHOD3(load, bool(std::string fileName, std::string id, SDL_Renderer * pRenderer));

        MOCK_METHOD10(drawTile, void(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, Renderer * pRenderer));
    };

    class FakeObject : public SDLGameObject {

    };
// @formatter:on
    class TestWithMocks : public testing::Test {
    public:
        TestWithMocks() {
            LOG_INFO("CreatingMocks");
            ServiceLocator::provide(std::make_unique<NiceMock<mocks::TextureManagerMock>>());
            ServiceLocator::provide(std::make_unique<NiceMock<mocks::GameObjectFactoryMock>>());
        }

    protected:

        NiceMock<mocks::TextureManagerMock> *getManager() {
            TextureManager *pManager = ServiceLocator::textureManager();
            LOG_INFO("pManager: " << pManager);
            return dynamic_cast<NiceMock<mocks::TextureManagerMock> *>(pManager);
        }

        NiceMock<mocks::GameObjectFactoryMock> *getFactory() {
            GameObjectFactory *gameObjectFactory1 = ServiceLocator::gameObjectFactory();
            LOG_INFO("pGameObjectFactory: " << gameObjectFactory1);
            return dynamic_cast<NiceMock<mocks::GameObjectFactoryMock> *>(gameObjectFactory1);
        }

        virtual void TearDown() {
            LOG_INFO("TearDown:  " << ServiceLocator::textureManager() << " and " << ServiceLocator::gameObjectFactory());
            ServiceLocator::clear();
        }
    };
}

