#include <base/GameObjectFactory.h>
#include <base/GameObject.h>
#include <TextureManager.h>
#include <sdl/SDLGameObject.h>
#include "gmock/gmock.h"

namespace mocks {
    class GameObjectFactoryMock : public GameObjectFactory {
    public:
        MOCK_METHOD1(create, GameObject *(std::string typeID));
    };

    class TextureManagerMock : public TextureManager {
    public:
        MOCK_METHOD3(load, bool(std::string fileName, std::string id, SDL_Renderer * pRenderer));
        MOCK_METHOD10(drawTile, void(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, Renderer *pRenderer));
    };

    class FakeObject : public SDLGameObject {

    };
}

