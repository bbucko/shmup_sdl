#ifndef SHMUP_CAMERA_H
#define SHMUP_CAMERA_H


#include <sdl/SDLGameObject.h>

class Camera {
public :
    void update(vec2 velocity);

    vec2 getPosition();

private:
    vec2 m_position;
};


#endif //SHMUP_CAMERA_H
