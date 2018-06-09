#ifndef SHMUP_OBJECTFACTORY_H
#define SHMUP_OBJECTFACTORY_H

#include <map>
#include <utils/Logger.h>
#include "GameObject.h"

class BaseCreator {
public:
    virtual GameObject *createGameObject() const = 0;

    virtual ~BaseCreator() = default;
};

class GameObjectFactory {
public:
    virtual bool registerType(std::string typeID, BaseCreator *pCreator);

    virtual GameObject *create(std::string typeID);

    virtual ~GameObjectFactory() {
        for (auto creator : m_creators) {
            delete creator.second;
        }
        m_creators.clear();
    }

private:
    std::map<std::string, BaseCreator *> m_creators;
};

#endif  // SHMUP_OBJECTFACTORY_H
