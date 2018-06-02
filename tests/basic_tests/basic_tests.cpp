#include <Player.h>

#include "gtest/gtest.h"

TEST(BasicCheck, TestEquality) {
    Player *player = new Player();
    player->load(new LoaderParams(1, 1, 1, 1, "abc"));
    player->update();
    player->update();
    player->update();

    EXPECT_EQ(true, true);
}
