#include "ServiceLocator.h"

std::unique_ptr<BulletHandler> ServiceLocator::m_bulletHandler;
std::unique_ptr<TextureManager> ServiceLocator::m_textureManager;
std::unique_ptr<GameObjectFactory> ServiceLocator::m_gameObjectFactory;
Renderer *ServiceLocator::m_renderer;

TextureManager *ServiceLocator::textureManager() {
    return ServiceLocator::m_textureManager.get();
}

BulletHandler *ServiceLocator::bulletHandler() {
    return ServiceLocator::m_bulletHandler.get();
}

GameObjectFactory *ServiceLocator::gameObjectFactory() {
    return ServiceLocator::m_gameObjectFactory.get();
}

Renderer *ServiceLocator::renderer() {
    return ServiceLocator::m_renderer;
}

void ServiceLocator::provide(std::unique_ptr<TextureManager> textureManager) {
    ServiceLocator::m_textureManager = std::move(textureManager);
}

void ServiceLocator::provide(std::unique_ptr<BulletHandler> bulletHandler) {
    ServiceLocator::m_bulletHandler = std::move(bulletHandler);
}

void ServiceLocator::provide(std::unique_ptr<GameObjectFactory> gameObjectFactory) {
    ServiceLocator::m_gameObjectFactory = std::move(gameObjectFactory);
}

void ServiceLocator::provide(Renderer *renderer) {
    ServiceLocator::m_renderer = renderer;
}
