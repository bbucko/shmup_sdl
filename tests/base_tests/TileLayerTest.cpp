#include <utils/Logger.h>
#include <base/ServiceLocator.h>
#include <base/TileLayer.h>
#include "gtest/gtest.h"
#include "mocks/Mocks.h"

namespace {

    using ::testing::Return;
    using ::testing::NiceMock;
    using ::testing::Mock;
    using ::testing::_;

    class TileLayerTest : public mocks::TestWithMocks {
    };

    TEST_F(TileLayerTest, UpdateTest) {
        auto tileIds = std::vector<std::vector<int>>(2);

        tileIds[0] = {0, 1};
        tileIds[1] = {1, 0};

        std::vector<Tileset> tilesets = std::vector<Tileset>(1);
        tilesets[0] = Tileset{1, 64, 64, 1, 1, 3, 3, 3, "tile1"};

        auto tileLayer = new TileLayer(32, 2, 2, tilesets, tileIds);
        tileLayer->update();

    }

    TEST_F(TileLayerTest, RenderTest) {
        EXPECT_CALL((*getCamera()), getPosition())
                .WillOnce(Return(vec2(0, 0)));

        EXPECT_CALL((*getManager()), draw("tile1", 1, 1, 0, 0, 32, 32, 0, 0));

        auto numOfRows = 16;
        auto numOfColumns = 20;
        auto tileIds = std::vector<std::vector<int>>(numOfRows);
        auto row = std::vector<int>(numOfColumns);

        for (int i = 0; i < numOfRows; i++) {
            tileIds.push_back(row);
            std::vector<int> &emptyRow = tileIds.at(i);
            for (int j = 0; j < numOfColumns; j++) {
                emptyRow.push_back(0);
            }
        }

        tileIds[0][0] = 1;

        std::vector<Tileset> tilesets = std::vector<Tileset>(1);
        tilesets[0] = Tileset{1, 32, 32, 1, 1, 3, 3, 3, "tile1"};

        auto tileLayer = new TileLayer(32, 2, 2, tilesets, tileIds);
        tileLayer->render();

    }

}
