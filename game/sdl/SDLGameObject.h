#ifndef SHMUP_SDLGAMEOBJECT_H
#define SHMUP_SDLGAMEOBJECT_H

#include "base/GameObject.h"

#include <glm/vec2.hpp>

typedef glm::vec2 Vector2D;

class SDLGameObject : public GameObject {
protected:
    Vector2D m_position;
    Vector2D m_velocity;
    Vector2D m_acceleration;

    int m_width;
    int m_height;

    int m_currentRow;
    int m_currentFrame;

    std::string m_textureID;
public:

    explicit SDLGameObject(const LoaderParams *pParams);

    void draw() override;

    void update() override;

    void clean() override;
};

#endif //SHMUP_SDLGAMEOBJECT_H