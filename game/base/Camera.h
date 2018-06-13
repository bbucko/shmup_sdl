#ifndef SHMUP_CAMERA_H
#define SHMUP_CAMERA_H


#include <sdl/SDLGameObject.h>

class Camera {
public :
    void update(vec2 velocity);

    vec2 getPosition();

    Camera() {
        m_position = vec2(0, 1440);
    }

private:
    vec2 m_position;
};


#endif //SHMUP_CAMERA_H
