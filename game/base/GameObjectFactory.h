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

    ~GameObjectFactory() {
        auto i = std::begin(m_creators);
        while (i != std::end(m_creators)) {
            delete (*i).second;
            i = m_creators.erase(i);
        }
    }

private:

    std::map<std::string, BaseCreator *> m_creators;
};


#endif //SHMUP_OBJECTFACTORY_H
