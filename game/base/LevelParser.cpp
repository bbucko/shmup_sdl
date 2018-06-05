#include <utils/Logger.h>
#include <utils/StringUtils.h>
#include <ServiceLocator.h>
#include "LevelParser.h"
#include "TileLayer.h"
#include <libgen.h>

using namespace tinyxml2;

Level *LevelParser::parseLevel(const char *levelFile) {
    LOG_INFO("Load level " << levelFile);
    auto filename = new char[sizeof(levelFile)];
    strcpy(filename, levelFile);
    m_dir = dirname(filename);
    delete[] filename;

    XMLDocument doc;
    auto result = doc.LoadFile(levelFile);

    if (result == XML_SUCCESS) {
        auto pRoot = doc.RootElement();
        if (StringUtils::equalsIgnoreCase(pRoot->Value(), "map")) {
            auto pLevel = new Level();

            for (auto a = pRoot->FirstAttribute(); a; a = a->Next()) {
                if (StringUtils::equalsIgnoreCase(a->Name(), "tilewidth")) { m_tileSize = a->IntValue(); }
                if (StringUtils::equalsIgnoreCase(a->Name(), "width")) { m_width = a->IntValue(); }
                if (StringUtils::equalsIgnoreCase(a->Name(), "height")) { m_height = a->IntValue(); }
            }

            for (auto *pElementRoot = pRoot->FirstChildElement(); pElementRoot != nullptr; pElementRoot = pElementRoot->NextSiblingElement()) {
                auto elementValue = std::string(pElementRoot->Value());
                if (StringUtils::equalsIgnoreCase(elementValue, "tileset")) {
                    parseTilesets(pElementRoot, pLevel->getTilesets());
                } else if (StringUtils::equalsIgnoreCase(elementValue, "layer")) {
                    parseTileLayer(pElementRoot, pLevel->getLayers(), pLevel->getTilesets());
                }
            }
            return pLevel;
        }
    }

    return nullptr;
}

void LevelParser::parseTilesets(XMLElement *pTilesetRoot, std::vector<Tileset> *pTilesets) {
    std::string source;
    std::string firstGid;

    for (auto a = pTilesetRoot->FirstAttribute(); a; a = a->Next()) {
        if (StringUtils::equalsIgnoreCase(a->Name(), "source")) { source = std::string(m_dir) + "/" + a->Value(); }
        if (StringUtils::equalsIgnoreCase(a->Name(), "firstgid")) { firstGid = a->Value(); }
    }

    XMLDocument doc;
    auto result = doc.LoadFile(source.c_str());
    LOG_INFO("open: " << source);
    if (result == XML_SUCCESS) {
        auto pRoot = doc.RootElement();
        Tileset tileset;

        std::string name;
        for (auto a = pRoot->FirstAttribute(); a; a = a->Next()) {
            if (StringUtils::equalsIgnoreCase(a->Name(), "name")) { name = a->Value(); }
        }

        if (!name.empty()) {
            for (auto *pElementRoot = pRoot->FirstChildElement(); pElementRoot != nullptr; pElementRoot = pElementRoot->NextSiblingElement()) {
                auto elementValue = std::string(pElementRoot->Value());
                if (StringUtils::equalsIgnoreCase(elementValue, "image")) {
                    for (auto a = pTilesetRoot->FirstAttribute(); a; a = a->Next()) {
                        if (StringUtils::equalsIgnoreCase(a->Name(), "source")) {
                            auto filename = std::string(m_dir) + "/" + a->Value();
                            ServiceLocator::textureManager()->load(filename, name, ServiceLocator::renderer());


                        }
                    }
                }
            }
            pTilesets->push_back(tileset);
        }
    }
}

void LevelParser::parseTileLayer(XMLElement *pTileElement, std::vector<Layer *> *pLayers,
                                 const std::vector<Tileset> *pTilesets) {
    std::string name;
    int width, height;
    for (auto a = pTileElement->FirstAttribute(); a; a = a->Next()) {
        if (StringUtils::equalsIgnoreCase(a->Name(), "name")) { name = a->Value(); }
        if (StringUtils::equalsIgnoreCase(a->Name(), "width")) { width = a->IntValue(); }
        if (StringUtils::equalsIgnoreCase(a->Name(), "height")) { height = a->IntValue(); }
    }

    auto pTileLayer = new TileLayer(m_tileSize, *pTilesets);
    pLayers->push_back(pTileLayer);
}