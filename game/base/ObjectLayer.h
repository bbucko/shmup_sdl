#ifndef SHMUP_OBJECTLAYER_H
#define SHMUP_OBJECTLAYER_H

#include <base/GameObject.h>
#include <sdl/SDLGameObject.h>
#include <utils/Memory.h>
#include "Layer.h"

class ObjectLayer : public Layer {
public:
    void render() override;

    void update() override;

    std::vector<GameObject *> *getObjects();

    ~ObjectLayer() override { DELETE_VECTOR(m_objects); }

private:
    std::vector<GameObject *> m_objects;

    void calculateCollisions();

    bool checkCollision(SDLGameObject *p1, SDLGameObject *p2);
};

#endif  // SHMUP_OBJECTLAYER_H
