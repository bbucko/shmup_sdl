#include "GameObjectFactory.h"
#include "Logger.h"

bool GameObjectFactory::registerType(std::string typeID, BaseCreator *pCreator) {
    auto it = m_creators.find(typeID);

    if (it != m_creators.end()) {
        delete pCreator;
        return false;
    }

    m_creators[typeID] = pCreator;

    return true;
}

GameObject *GameObjectFactory::create(std::string typeID) {
    auto it = m_creators.find(typeID);

    if (it == m_creators.end()) {
        LOG_INFO("could not find type: " << typeID);
        return nullptr;
    }

    BaseCreator *pCreator = (*it).second;
    return pCreator->createGameObject();
}