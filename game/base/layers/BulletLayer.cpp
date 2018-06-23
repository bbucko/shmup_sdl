

#include <base/ServiceLocator.h>
#include "BulletLayer.h"

void BulletLayer::render() {
    ServiceLocator::bulletHandler()->render();

}

void BulletLayer::update() {
    ServiceLocator::bulletHandler()->update();

}

BulletLayer::~BulletLayer() {

}
