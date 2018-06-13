#include "ServiceLocator.h"

std::unique_ptr<BulletHandler> ServiceLocator::s_bulletHandler;
std::unique_ptr<TextureManager> ServiceLocator::s_textureManager;
std::unique_ptr<GameObjectFactory> ServiceLocator::s_gameObjectFactory;
std::unique_ptr<Camera> ServiceLocator::s_camera;
Renderer *ServiceLocator::s_renderer;

TextureManager *ServiceLocator::textureManager() {
    return ServiceLocator::s_textureManager.get();
}

BulletHandler *ServiceLocator::bulletHandler() {
    return ServiceLocator::s_bulletHandler.get();
}

GameObjectFactory *ServiceLocator::gameObjectFactory() {
    return ServiceLocator::s_gameObjectFactory.get();
}

Camera *ServiceLocator::camera() {
    return ServiceLocator::s_camera.get();
}

Renderer *ServiceLocator::renderer() {
    return ServiceLocator::s_renderer;
}

void ServiceLocator::provide(std::unique_ptr<TextureManager> textureManager) {
    ServiceLocator::s_textureManager = std::move(textureManager);
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

void ServiceLocator::provide(Renderer *renderer) {
    ServiceLocator::s_renderer = renderer;
}
