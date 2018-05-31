#ifndef SHMUP_SDLGAMEOBJECT_H
#define SHMUP_SDLGAMEOBJECT_H

#include "base/GameObject.h"

#include <glm/vec2.hpp>

typedef glm::vec2 vec2;

class SDLGameObject : public GameObject {
protected:
    vec2 m_position;
    vec2 m_velocity;
    vec2 m_acceleration;

    int m_width;
    int m_height;

    int m_currentRow;
    int m_currentFrame;

    int m_maxFrames = 1;

    std::string m_textureID;
public:

    explicit SDLGameObject(const LoaderParams *pParams);

    void draw() override;

    void update() override;

    void clean() override;
};

#endif //SHMUP_SDLGAMEOBJECT_H