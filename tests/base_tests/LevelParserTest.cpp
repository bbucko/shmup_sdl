#include <utils/Logger.h>
#include <base/LevelParser.h>
#include <ServiceLocator.h>

#include "gtest/gtest.h"
#include "mocks/Mocks.h"

namespace {

    using ::testing::Return;
    using ::testing::NiceMock;
    using ::testing::Mock;
    using ::testing::_;

    class LevelParserTest : public testing::Test {
    public:
        LevelParserTest() {
            ServiceLocator::provide(&manager);
            ServiceLocator::provide(&factory);
        }

        NiceMock<mocks::TextureManagerMock> manager;
        NiceMock<mocks::GameObjectFactoryMock> factory;
    protected:
        virtual void TearDown() {
            Mock::VerifyAndClear(&manager);
            Mock::VerifyAndClear(&factory);
        }
    };

    TEST_F(LevelParserTest, ParserTest) {
        EXPECT_CALL(manager, load("/tmp/shmup_tests/tiles.tsx", "tiles", _))
                .WillOnce(Return(true));

        auto pLevel = LevelParser::Instance().parseLevel("/tmp/shmup_tests/map1.tmx");

        EXPECT_NE(pLevel, nullptr);
    }

}
