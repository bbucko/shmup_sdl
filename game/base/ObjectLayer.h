#ifndef SHMUP_OBJECTLAYER_H
#define SHMUP_OBJECTLAYER_H

#include <base/GameObject.h>
#include "Layer.h"

class ObjectLayer : public Layer {
public:
    void render() override;

    void update() override;

    std::vector<GameObject *> *getObjects();

    ~ObjectLayer(){
        for(auto object : m_objects){
            delete object;
        }

        m_objects.clear();
    }

private:
    std::vector<GameObject *> m_objects;
};

#endif  // SHMUP_OBJECTLAYER_H
