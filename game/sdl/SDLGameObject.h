#ifndef SHMUP_SDLGAMEOBJECT_H
#define SHMUP_SDLGAMEOBJECT_H

#include "base/GameObject.h"

#include <glm/vec2.hpp>


class SDLGameObject : public GameObject {
protected:
    glm::vec2 m_position;

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