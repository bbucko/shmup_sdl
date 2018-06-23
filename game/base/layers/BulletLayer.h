

#ifndef SHMUP_BULLETLAYER_H
#define SHMUP_BULLETLAYER_H


#include <base/Layer.h>

class BulletLayer : public Layer {
public:
    void render() override;

    void update() override;

    ~BulletLayer() override;

};


#endif //SHMUP_BULLETLAYER_H
