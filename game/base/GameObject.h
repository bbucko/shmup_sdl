#ifndef SHMUP_GAMEOBJECT_H
#define SHMUP_GAMEOBJECT_H

#include "LoaderParams.h"
#include <memory>

class GameObject {
public:
     virtual void draw() = 0 ;

    virtual void update() = 0;

    virtual void clean() = 0;

    virtual void load(std::unique_ptr<LoaderParams> const &pParams) = 0;

    virtual ~GameObject() = default;
};

#endif  // SHMUP_GAMEOBJECT_H
