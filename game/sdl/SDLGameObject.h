#ifndef SHMUP_SDLGAMEOBJECT_H
#define SHMUP_SDLGAMEOBJECT_H

#include "base/GameObject.h"

class SDLGameObject : public GameObject, public Positionable, public Movable {
protected:

    int m_width{};
    int m_height{};

    int m_currentRow{};
    int m_currentFrame{};

    int m_numFrames{};

    std::string m_textureID;

    bool hasCollided{false};

public:
    explicit SDLGameObject(int id) : GameObject(id) {};

    void load(std::unique_ptr<LoaderParams> pParams) override;

    void draw() override;

    void update() override;

    void clean() override;

    inline float getWidth() const { return m_width; }

    inline float getHeight() const { return m_height; }
};

#endif  // SHMUP_SDLGAMEOBJECT_H