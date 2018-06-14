#ifndef SHMUP_LAYER_CPP_H
#define SHMUP_LAYER_CPP_H

#include <vector>
#include <utils/Memory.h>

class Layer {
public:
    virtual void render() = 0;

    virtual void update() = 0;

    virtual ~Layer() { DELETE_VECTOR(m_layers); };
protected:

private:
    std::vector<Layer *> m_layers;
};

#endif  // SHMUP_LAYER_CPP_H
