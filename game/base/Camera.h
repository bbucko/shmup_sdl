#ifndef SHMUP_CAMERA_H
#define SHMUP_CAMERA_H


#include <sdl/SDLGameObject.h>

class Camera {
public :
    virtual void update();

    virtual vec2 getPosition() { return m_position; }

    virtual vec2 getVelocity() { return m_velocity; }

    Camera() {
        m_position = vec2(0, 1440);
        m_velocity = vec2(0, -1);
    }

    virtual ~Camera() = default;

private:
    vec2 m_position{};
    vec2 m_velocity{};
};


#endif //SHMUP_CAMERA_H
