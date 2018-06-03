#include <base/StateParser.h>
#include "gtest/gtest.h"

static void cleanup(std::vector<GameObject *> vector, std::vector<std::string> ids) {
    for (auto object : vector) {
        delete object;
    }

    vector.clear();
    ids.clear();
}

TEST(StateParserTest, NotExistingFileTest) {
    std::vector<GameObject *> objects;
    std::vector<std::string> textureIds;
    auto parser = StateParser();
    bool result = parser.parseState("/tmp/shmup_tests/invalid.xml", "", &objects, &textureIds);

    EXPECT_EQ(result, false);
    EXPECT_EQ(objects.size(), 0);
}

TEST(StateParserTest, MenuStateTest) {
    std::vector<GameObject *> objects;
    std::vector<std::string> textureIds;

    auto parser = StateParser();
    bool result = parser.parseState("/tmp/shmup_tests/test.xml", "menu", &objects, &textureIds);

    EXPECT_EQ(result, true);
    EXPECT_EQ(objects.size(), 2);
    EXPECT_EQ(textureIds.size(), 2);

    EXPECT_EQ(textureIds[0], "playbutton");
    EXPECT_EQ(textureIds[1], "exitbutton");

    cleanup(objects, textureIds);
}

TEST(StateParserTest, PlayStateTest) {
    std::vector<GameObject *> objects;
    std::vector<std::string> textureIds;

    auto parser = StateParser();
    bool result = parser.parseState("/tmp/shmup_tests/test.xml", "play", &objects, &textureIds);

    EXPECT_EQ(result, true);
    EXPECT_EQ(objects.size(), 0);
    EXPECT_EQ(textureIds.size(), 0);
}
