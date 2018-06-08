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
    virtual bool registerType(std::string typeID, BaseCreator *pCreator);

    virtual GameObject *create(std::string typeID);

    virtual ~GameObjectFactory() {
        auto i = std::begin(m_creators);
        while (i != std::end(m_creators)) {
            delete (*i).second;
            i = m_creators.erase(i);
        }
    }

private:
    std::map<std::string, BaseCreator *> m_creators;
};

#endif  // SHMUP_OBJECTFACTORY_H
