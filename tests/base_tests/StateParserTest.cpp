#include <ServiceLocator.h>
#include <utils/Logger.h>
#include <base/StateParser.h>
#include <base/GameObjectFactory.h>

#include "gtest/gtest.h"
#include "mocks/Mocks.h"

namespace {

    using ::testing::Return;
    using ::testing::NiceMock;
    using ::testing::Mock;
    using ::testing::_;

    class StateParserTest : public testing::Test {

    public:
        StateParserTest() {
            ServiceLocator::provide(&manager);
            ServiceLocator::provide(&factory);
        }

        std::vector<GameObject *> objects;
        std::vector<std::string> textureIds;

        NiceMock<mocks::TextureManagerMock> manager;
        NiceMock<mocks::GameObjectFactoryMock> factory;
    protected:
        virtual void TearDown() {
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
        mocks::FakeObject fakeObject;

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
