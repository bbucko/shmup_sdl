#include <base/StateParser.h>
#include <base/GameObjectFactory.h>
#include <utils/Logger.h>
#include <ServiceLocator.h>
#include <sdl/SDLGameObject.h>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace {

    using ::testing::Return;
    using ::testing::NiceMock;
    using ::testing::Mock;
    using ::testing::_;

    class GameObjectFactoryMock : public GameObjectFactory {
    public:
        MOCK_METHOD1(create, GameObject *(std::string typeID));
    };

    class TextureManagerMock : public TextureManager {
    public:
        MOCK_METHOD3(load, bool(std::string fileName, std::string id, SDL_Renderer * pRenderer));

    };

    class FakeObject : public SDLGameObject {

    };

    class StateParserTest : public testing::Test {

    public:
        StateParserTest() {
            ServiceLocator::provide(&manager);
            ServiceLocator::provide(&factory);
        }


    protected:
        std::vector<GameObject *> objects;
        std::vector<std::string> textureIds;

        NiceMock<TextureManagerMock> manager;
        NiceMock<GameObjectFactoryMock> factory;

        virtual void SetUp() {
            LOG_INFO("setup");

        }

        virtual void TearDown() {
            LOG_INFO("teardown");

            objects.clear();
            textureIds.clear();

            Mock::VerifyAndClear(&manager);
            Mock::VerifyAndClear(&factory);
        }
    };

    TEST_F(StateParserTest, NotExistingFileTest) {
        auto parser = StateParser();
        auto result = parser.parseState("/tmp/shmup_tests/invalid.xml", "", &objects, &textureIds);

        EXPECT_EQ(result, false);
        EXPECT_EQ(objects.size(), 0);
    }

    TEST_F(StateParserTest, MenuStateTest) {
        FakeObject fakeObject;

        EXPECT_CALL(factory, create("FakeObject"))
                .Times(2)
                .WillRepeatedly(Return(&fakeObject));

        EXPECT_CALL(manager, load("sample1.png", "texture1", _))
                .WillOnce(Return(true));
        EXPECT_CALL(manager, load("sample2.png", "texture2", _))
                .WillOnce(Return(true));

        auto parser = StateParser();
        auto result = parser.parseState("/tmp/shmup_tests/test.xml", "menu", &objects, &textureIds);

        EXPECT_EQ(result, true);
        EXPECT_EQ(objects.size(), 2);
        EXPECT_EQ(textureIds.size(), 2);

        EXPECT_EQ(textureIds[0], "texture1");
        EXPECT_EQ(textureIds[1], "texture2");
    }

    TEST_F(StateParserTest, PlayStateTest) {
        auto parser = StateParser();
        auto result = parser.parseState("/tmp/shmup_tests/test.xml", "play", &objects, &textureIds);

        EXPECT_EQ(result, true);
        EXPECT_EQ(objects.size(), 0);
        EXPECT_EQ(textureIds.size(), 0);
    }
}
