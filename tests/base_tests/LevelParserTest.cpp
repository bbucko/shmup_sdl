#include <utils/Logger.h>
#include <base/LevelParser.h>
#include <ServiceLocator.h>
#include <base/TileLayer.h>
#include <base/ObjectLayer.h>

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

    TEST_F(LevelParserTest, SingleLayerAndTileset) {
        mocks::FakeObject fakeObject;

        EXPECT_CALL(manager, load("/tmp/shmup_tests/tiles.png", "tiles", _))
                .WillOnce(Return(true));

        EXPECT_CALL(factory, create("Player"))
                .WillOnce(Return(&fakeObject));

        EXPECT_CALL(factory, create("enemy"))
                .Times(2)
                .WillRepeatedly(Return(&fakeObject));

        auto pLevel = LevelParser::Instance().parseLevel("/tmp/shmup_tests/map1.tmx");

        std::vector<Tileset> *pVector = pLevel->getTilesets();
        EXPECT_EQ(pVector->size(), 1);

        Tileset &tileset = pVector->at(0);
        EXPECT_EQ(tileset.name, "tiles");
        EXPECT_EQ(tileset.height, 67);
        EXPECT_EQ(tileset.width, 196);
        EXPECT_EQ(tileset.firstGridID, 1);
        EXPECT_EQ(tileset.tileHeight, 64);
        EXPECT_EQ(tileset.tileWidth, 64);
        EXPECT_EQ(tileset.spacing, 1);
        EXPECT_EQ(tileset.margin, 1);
        EXPECT_EQ(tileset.numColumns, 3);

        auto layers = pLevel->getLayers();
        EXPECT_EQ(layers->size(), 2);

        auto tileLayer = dynamic_cast<TileLayer *>(layers->at(0));

        auto objectLayer = dynamic_cast<ObjectLayer *>(layers->at(1));
        EXPECT_EQ(objectLayer->getObjects()->size(), 3);
    }

}
