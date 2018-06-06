

#ifndef SHMUP_OBJECTLAYER_H
#define SHMUP_OBJECTLAYER_H


#include "Layer.h"

class ObjectLayer : public Layer {
public:
    void render() override;

    void update() override;
};


#endif //SHMUP_OBJECTLAYER_H
