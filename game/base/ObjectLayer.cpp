

#include "ObjectLayer.h"

void ObjectLayer::update() {
    for (auto object : m_objects) {
        object->update();
    }

}

void ObjectLayer::render() {
    for (auto object : m_objects) {
        object->draw();
    }
}

std::vector<GameObject *> *ObjectLayer::getObjects() {
    return &m_objects;
}