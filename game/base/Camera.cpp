

#include "Camera.h"

void Camera::update(vec2 velocity) {
    m_position += velocity;
}

vec2 Camera::getPosition() {
    return m_position;
}
