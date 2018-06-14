#include "GameObjectFactory.h"

bool GameObjectFactory::registerType(const std::string &typeID, const BaseCreator *pCreator) {
    LOG_INFO("registering new type: " << typeID);
    auto it = m_creators.find(typeID);

    if (it != m_creators.end()) {
        delete pCreator;
        return false;
    }

    m_creators[typeID] = pCreator;

    return true;
}

GameObject *GameObjectFactory::create(int id, const std::string &typeID) {
    auto it = m_creators.find(typeID);

    if (it == m_creators.end()) {
        LOG_INFO("could not find type: " << typeID);
        return nullptr;
    }
    LOG_INFO("Creating object: " << typeID << " with id: " << id);
    const BaseCreator *pCreator = (*it).second;
    return pCreator->createGameObject(id);
}