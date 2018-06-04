#include "ServiceLocator.h"

BulletHandler *ServiceLocator::m_bulletHandler;
TextureManager *ServiceLocator::m_textureManager;
GameObjectFactory *ServiceLocator::m_gameObjectFactory;
Renderer *ServiceLocator::m_renderer;

TextureManager *ServiceLocator::textureManager() {
    return ServiceLocator::m_textureManager;
}

BulletHandler *ServiceLocator::bulletHandler() {
    return ServiceLocator::m_bulletHandler;
}

GameObjectFactory *ServiceLocator::gameObjectFactory() {
    return ServiceLocator::m_gameObjectFactory;
}

Renderer *ServiceLocator::renderer() {
    return ServiceLocator::m_renderer;
}

void ServiceLocator::provide(TextureManager *textureManager) {
    ServiceLocator::m_textureManager = textureManager;
}

void ServiceLocator::provide(BulletHandler *bulletHandler) {
    ServiceLocator::m_bulletHandler = bulletHandler;
}

void ServiceLocator::provide(GameObjectFactory *gameObjectFactory) {
    ServiceLocator::m_gameObjectFactory = gameObjectFactory;
}

void ServiceLocator::provide(Renderer *renderer) {
    ServiceLocator::m_renderer = renderer;
}
