#ifndef SHMUP_OBJECTLAYER_H
#define SHMUP_OBJECTLAYER_H

#include <base/GameObject.h>
#include <utils/Memory.h>
#include "base/Layer.h"

class ObjectLayer : public Layer {
public:
    void render() override;

    void update() override;

    inline std::vector<GameObject *> *getObjects() { return &m_objects; };

    ~ObjectLayer() override { DELETE_VECTOR(m_objects); }

private:
    std::vector<GameObject *> m_objects;
};

#endif  // SHMUP_OBJECTLAYER_H
