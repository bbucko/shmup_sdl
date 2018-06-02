#include <base/StateParser.h>
#include "gtest/gtest.h"

TEST(StateParserTest, NotExistingFileTest) {
    std::vector<GameObject *> objects;
    std::vector<std::string> textureIds;
    auto parser = StateParser();
    bool result = parser.parseState("invalid.xml", "", &objects, &textureIds);

    EXPECT_EQ(result, false);
    EXPECT_EQ(objects.size(), 0);
}

TEST(StateParserTest, MenuStateTest) {
    std::vector<GameObject *> objects;
    std::vector<std::string> textureIds;

    auto parser = StateParser();
    bool result = parser.parseState("..//assets/test.xml", "menu", &objects, &textureIds);

    EXPECT_EQ(result, true);
    EXPECT_EQ(objects.size(), 2);
    EXPECT_EQ(textureIds.size(), 2);
}

TEST(StateParserTest, PlayStateTest) {
    std::vector<GameObject *> objects;
    std::vector<std::string> textureIds;

    auto parser = StateParser();
    bool result = parser.parseState("..//assets/test.xml", "play", &objects, &textureIds);

    EXPECT_EQ(result, true);
    EXPECT_EQ(objects.size(), 0);
    EXPECT_EQ(textureIds.size(), 0);

}