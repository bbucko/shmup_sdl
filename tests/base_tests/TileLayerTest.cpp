#include <utils/Logger.h>
#include <ServiceLocator.h>
#include <base/TileLayer.h>

#include "gtest/gtest.h"
#include "mocks/Mocks.h"

namespace {

    using ::testing::Return;
    using ::testing::NiceMock;
    using ::testing::Mock;
    using ::testing::_;

    class TileLayerTest : public testing::Test {
    public:
        TileLayerTest() {
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

    TEST_F(TileLayerTest, UpdateTest) {
        auto tileIds = std::vector<std::vector<int>>(2);

        tileIds[0] = {0, 1};
        tileIds[1] = {1, 0};

        std::vector<Tileset> tilesets = std::vector<Tileset>(1);
        tilesets[0] = Tileset{"tile1", 1, 64, 64, 1, 1, 3, 3, 3};

        auto tileLayer = new TileLayer(32, tilesets, tileIds);
        tileLayer->update();

    }

    TEST_F(TileLayerTest, RenderTest) {
        EXPECT_CALL(manager, drawTile("tile1", 2, 2, 32, 0, 32, 32, 0, 0, _));

        auto tileIds = std::vector<std::vector<int>>(2);

        tileIds[0] = {0, 1};
        tileIds[1] = {1, 0};

        std::vector<Tileset> tilesets = std::vector<Tileset>(1);
        tilesets[0] = Tileset{"tile1", 1, 64, 64, 1, 1, 3, 3, 3};

        auto tileLayer = new TileLayer(32, tilesets, tileIds);
        tileLayer->render();

    }

}
