#ifndef SHMUP_SDLGAMEOBJECT_H
#define SHMUP_SDLGAMEOBJECT_H

#include "base/GameObject.h"

class SDLGameObject : public GameObject {
protected:
    int m_x;
    int m_y;

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