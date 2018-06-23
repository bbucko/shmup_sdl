#include "ObjectLayer.h"
#include "base/ServiceLocator.h"

void ObjectLayer::update() {
    for (auto object : m_objects) {
        object->update();
    }

    ServiceLocator::collisionManager()->checkCollisions(m_objects);
}

void ObjectLayer::render() {
    for (auto object : m_objects) {
        object->draw();
    }
}