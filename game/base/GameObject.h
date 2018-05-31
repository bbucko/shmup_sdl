#ifndef SHMUP_GAMEOBJECT_H
#define SHMUP_GAMEOBJECT_H

#include "LoaderParams.h"

class GameObject {

protected:
    const LoaderParams *m_pParams;

public:

    virtual void draw() = 0;

    virtual void update()= 0;

    virtual void clean() = 0;

    GameObject() = default;


protected:
    explicit GameObject(const LoaderParams *pParams) : m_pParams(pParams) {};

    virtual ~GameObject() = default;
};


#endif //SHMUP_GAMEOBJECT_H
