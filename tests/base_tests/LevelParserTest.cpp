#include <utils/Logger.h>
#include <base/LevelParser.h>
#include "gtest/gtest.h"

namespace {

    class LevelParserTest : public testing::Test {

    protected:

        virtual void SetUp() {
            LOG_INFO("setup");
        }

        virtual void TearDown() {
            LOG_INFO("teardown");
        }
    };

    TEST_F(LevelParserTest, NotExistingFileTest) {
        LevelParser::Instance().parseLevel("");

    }

}
