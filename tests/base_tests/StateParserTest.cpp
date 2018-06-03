#include <base/StateParser.h>
#include <base/GameObjectFactory.h>
#include <sdl/SDLGameObject.h>
#include <base/Logger.h>
#include "gtest/gtest.h"


namespace {

    class StateParserTest : public testing::Test {
    private:
        class FakeObject : public SDLGameObject {

        };

        class FakeObjectCreator : public BaseCreator {

        public:
            GameObject *createGameObject() const override {
                return new FakeObject();
            }
        };

    protected:
        StateParserTest() : Test() {
            GameObjectFactory::Instance().registerType("FakeObject", new FakeObjectCreator());
        }

    protected:
        std::vector<GameObject *> objects;
        std::vector<std::string> textureIds;

        virtual void SetUp() {
            LOG_INFO("setup");
        }

        virtual void TearDown() {
            LOG_INFO("teardown");

            for (auto object : objects) {
                delete object;
            }

            objects.clear();
            textureIds.clear();
        }

    };

    TEST_F(StateParserTest, NotExistingFileTest) {
        auto parser = StateParser();
        bool result = parser.parseState("/tmp/shmup_tests/invalid.xml", "", &objects, &textureIds);

        EXPECT_EQ(result, false);
        EXPECT_EQ(objects.size(), 0);
    }

    TEST_F(StateParserTest, MenuStateTest) {
        auto parser = StateParser();
        bool result = parser.parseState("/tmp/shmup_tests/test.xml", "menu", &objects, &textureIds);

        EXPECT_EQ(result, true);
        EXPECT_EQ(objects.size(), 2);
        EXPECT_EQ(textureIds.size(), 2);

        EXPECT_EQ(textureIds[0], "texture1");
        EXPECT_EQ(textureIds[1], "texture2");
    }

    TEST_F(StateParserTest, PlayStateTest) {
        auto parser = StateParser();
        bool result = parser.parseState("/tmp/shmup_tests/test.xml", "play", &objects, &textureIds);

        EXPECT_EQ(result, true);
        EXPECT_EQ(objects.size(), 0);
        EXPECT_EQ(textureIds.size(), 0);
    }
}
