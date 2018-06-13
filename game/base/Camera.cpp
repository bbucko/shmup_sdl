

#include "Camera.h"

void Camera::update(vec2 velocity) {
    m_position += velocity;
    if(m_position.y < 0) {
        m_position.y = 0;
    }
}

vec2 Camera::getPosition() {
    return m_position;
}
