#ifndef SHMUP_OBJECTFACTORY_H
#define SHMUP_OBJECTFACTORY_H

#include <map>
#include "GameObject.h"

class BaseCreator {
public:

    virtual GameObject *createGameObject() const = 0;

    virtual ~BaseCreator() = default;
};

class GameObjectFactory {
public:

    bool registerType(std::string typeID, BaseCreator *pCreator);

    GameObject *create(std::string typeID);

    static GameObjectFactory &Instance() {
        static GameObjectFactory instance;
        return instance;
    }

private:

    std::map<std::string, BaseCreator *> m_creators;
};


#endif //SHMUP_OBJECTFACTORY_H
