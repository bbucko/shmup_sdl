#ifndef SHMUP_CAMERA_H
#define SHMUP_CAMERA_H


#include <sdl/SDLGameObject.h>

class Camera {
public :
    void update();

    vec2 getPosition() { return m_position; }

    vec2 getVelocity() { return m_velocity; }

    Camera() {
        m_position = vec2(0, 1440);
        m_velocity = vec2(0, -1);
    }

private:
    vec2 m_position{};
    vec2 m_velocity{};
};


#endif //SHMUP_CAMERA_H
