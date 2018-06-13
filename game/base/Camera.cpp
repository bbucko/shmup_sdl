

#include "Camera.h"

void Camera::update() {
    m_position += m_velocity;
    if (m_position.y < 0) {
        m_velocity = vec2(0, 0);
    }
}

