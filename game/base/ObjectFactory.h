#ifndef SHMUP_OBJECTFACTORY_H
#define SHMUP_OBJECTFACTORY_H


#include "GameObject.h"

class ObjectFactory {

    GameObject *create(std::string id);

};


#endif //SHMUP_OBJECTFACTORY_H
