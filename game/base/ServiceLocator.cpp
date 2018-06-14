#include "ServiceLocator.h"

std::unique_ptr<BulletHandler> ServiceLocator::s_bulletHandler;
std::unique_ptr<TextureManager> ServiceLocator::s_textureManager;
std::unique_ptr<GameObjectFactory> ServiceLocator::s_gameObjectFactory;
std::unique_ptr<Camera> ServiceLocator::s_camera;
std::unique_ptr<CollisionManager> ServiceLocator::s_collisionManager;

TextureManager *ServiceLocator::textureManager() {
    return ServiceLocator::s_textureManager.get();
}

BulletHandler *ServiceLocator::bulletHandler() {
    return ServiceLocator::s_bulletHandler.get();
}

GameObjectFactory *ServiceLocator::gameObjectFactory() {
    return ServiceLocator::s_gameObjectFactory.get();
}

CollisionManager *ServiceLocator::collisionManager() {
    return ServiceLocator::s_collisionManager.get();
}

Camera *ServiceLocator::camera() {
    return ServiceLocator::s_camera.get();
}

void ServiceLocator::provide(std::unique_ptr<TextureManager> textureManager) {
    ServiceLocator::s_textureManager = std::move(textureManager);
}

void ServiceLocator::provide(std::unique_ptr<CollisionManager> collisionManager) {
    ServiceLocator::s_collisionManager = std::move(collisionManager);
}

void ServiceLocator::provide(std::unique_ptr<BulletHandler> bulletHandler) {
    ServiceLocator::s_bulletHandler = std::move(bulletHandler);
}

void ServiceLocator::provide(std::unique_ptr<GameObjectFactory> gameObjectFactory) {
    ServiceLocator::s_gameObjectFactory = std::move(gameObjectFactory);
}

void ServiceLocator::provide(std::unique_ptr<Camera> camera) {
    ServiceLocator::s_camera = std::move(camera);
}