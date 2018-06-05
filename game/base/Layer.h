#ifndef SHMUP_LAYER_CPP_H
#define SHMUP_LAYER_CPP_H

#include <vector>

class Layer {
public:

    virtual void render() = 0;

    virtual void update() = 0;

protected:

    virtual ~Layer() = default;

private:
    std::vector<Layer*> m_layers;

};

#endif //SHMUP_LAYER_CPP_H
