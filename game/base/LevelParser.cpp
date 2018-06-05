#include <utils/Logger.h>
#include <utils/StringUtils.h>
#include <ServiceLocator.h>
#include "LevelParser.h"
#include "TileLayer.h"
#include <libgen.h>

using namespace tinyxml2;

Level *LevelParser::parseLevel(const char *levelFile) {
    LOG_INFO("Load level " << levelFile);
    auto filename = new char[strlen(levelFile) + 1];

    strcpy(filename, levelFile);

    m_dir = dirname(filename);

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
    delete[] filename;
    return nullptr;
}

void LevelParser::parseTilesets(XMLElement *pTilesetRoot, std::vector<Tileset> *pTilesets) {
    std::string source;
    Tileset tileset{};

    for (auto a = pTilesetRoot->FirstAttribute(); a; a = a->Next()) {
        if (StringUtils::equalsIgnoreCase(a->Name(), "source")) { source = std::string(m_dir) + "/" + a->Value(); }
        if (StringUtils::equalsIgnoreCase(a->Name(), "firstgid")) { tileset.firstGridID = a->IntValue(); }
    }

    XMLDocument doc;
    auto result = doc.LoadFile(source.c_str());

    if (result == XML_SUCCESS) {
        auto pRoot = doc.RootElement();

        for (auto a = pRoot->FirstAttribute(); a; a = a->Next()) {
            if (StringUtils::equalsIgnoreCase(a->Name(), "name")) { tileset.name = a->Value(); }
            if (StringUtils::equalsIgnoreCase(a->Name(), "tilewidth")) { tileset.tileWidth = a->IntValue(); }
            if (StringUtils::equalsIgnoreCase(a->Name(), "tileheight")) { tileset.tileHeight = a->IntValue(); }
            if (StringUtils::equalsIgnoreCase(a->Name(), "spacing")) { tileset.spacing = a->IntValue(); }
            if (StringUtils::equalsIgnoreCase(a->Name(), "margin")) { tileset.margin = a->IntValue(); }
            if (StringUtils::equalsIgnoreCase(a->Name(), "columns")) { tileset.numColumns = a->IntValue(); }
        }

        for (auto *pElementRoot = pRoot->FirstChildElement(); pElementRoot != nullptr; pElementRoot = pElementRoot->NextSiblingElement()) {
            auto elementValue = std::string(pElementRoot->Value());
            if (StringUtils::equalsIgnoreCase(elementValue, "image")) {
                for (auto a = pElementRoot->FirstAttribute(); a; a = a->Next()) {
                    if (StringUtils::equalsIgnoreCase(a->Name(), "source")) {
                        auto imageFilename = std::string(m_dir) + "/" + a->Value();
                        LOG_INFO("Loading image: " << tileset.name << " from file: " << imageFilename);

                        ServiceLocator::textureManager()->load(imageFilename, tileset.name, ServiceLocator::renderer());
                    }

                    if (StringUtils::equalsIgnoreCase(a->Name(), "width")) { tileset.width = a->IntValue(); }
                    if (StringUtils::equalsIgnoreCase(a->Name(), "height")) { tileset.height = a->IntValue(); }
                }
            }


            LOG_INFO("Done creating tileset: " << tileset.name);
            pTilesets->push_back(tileset);
        }
    }
}

void LevelParser::parseTileLayer(XMLElement *pTileElement, std::vector<Layer *> *pLayers, const std::vector<Tileset> *pTilesets) {
    std::string name;

    for (auto a = pTileElement->FirstAttribute(); a; a = a->Next()) {
        if (StringUtils::equalsIgnoreCase(a->Name(), "name")) { name = a->Value(); }
        if (StringUtils::equalsIgnoreCase(a->Name(), "width")) { m_width = a->IntValue(); }
        if (StringUtils::equalsIgnoreCase(a->Name(), "height")) { m_height = a->IntValue(); }
    }

    auto pTileLayer = new TileLayer(m_tileSize, *pTilesets);
    pLayers->push_back(pTileLayer);
}