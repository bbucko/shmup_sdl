#ifndef SHMUP_OBJECTFACTORY_H
#define SHMUP_OBJECTFACTORY_H

#include <map>
#include <utils/Logger.h>
#include <utils/Memory.h>
#include "GameObject.h"

class BaseCreator {
public:
    virtual GameObject *createGameObject(int id) const = 0;

    virtual ~BaseCreator() = default;
};

class GameObjectFactory {
public:
    virtual bool registerType(const std::string &typeID, const BaseCreator *pCreator);

    virtual GameObject *create(int id, const std::string &typeID);

    virtual ~GameObjectFactory() { DELETE_MAP(m_creators); }

private:
    std::map<std::string, const BaseCreator *> m_creators;
};

#endif  // SHMUP_OBJECTFACTORY_H
