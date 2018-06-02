#ifndef SHMUP_GAMEOBJECT_H
#define SHMUP_GAMEOBJECT_H

#include "LoaderParams.h"

class GameObject {

protected:
    const LoaderParams *m_pParams;

public:

    virtual void draw() = 0;

    virtual void update() = 0;

    virtual void clean() = 0;

    virtual void load(const LoaderParams *pParams) = 0;

    virtual ~GameObject() = default;
};


#endif //SHMUP_GAMEOBJECT_H
