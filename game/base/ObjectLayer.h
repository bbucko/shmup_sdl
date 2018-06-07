#ifndef SHMUP_OBJECTLAYER_H
#define SHMUP_OBJECTLAYER_H


#include "Layer.h"
#include <base/GameObject.h>

class ObjectLayer : public Layer {
public:
    void render() override;

    void update() override;

    std::vector<GameObject *> *getObjects();

private:
    std::vector<GameObject *> m_objects;
};


#endif //SHMUP_OBJECTLAYER_H
