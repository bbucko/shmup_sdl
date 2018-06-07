#include "LevelParser.h"

#include <utils/Logger.h>
#include <utils/StringUtils.h>
#include <utils/Base64.h>
#include <ServiceLocator.h>
#include <libgen.h>
#include <zconf.h>
#include <zlib.h>

#include "TileLayer.h"

using namespace tinyxml2;

Level *LevelParser::parseLevel(const char *levelFile) {
    LOG_INFO("Load level " << levelFile);

    XMLDocument doc;

    XMLError result = loadRootXML(levelFile, doc);

    if (result == XML_SUCCESS) {
        auto pRoot = doc.RootElement();
        if (StringUtils::equalsIgnoreCase(pRoot->Value(), "map")) {
            auto pLevel = new Level();

            for (auto a = pRoot->FirstAttribute(); a; a = a->Next()) {
                attributeToInt(a, "tilewidth", &m_tileSize);
                attributeToInt(a, "width", &m_width);
                attributeToInt(a, "height", &m_height);
            }

            for (auto *pElementRoot = pRoot->FirstChildElement(); pElementRoot != nullptr; pElementRoot = pElementRoot->NextSiblingElement()) {
                processElement(pElementRoot, "tileset", pLevel, &LevelParser::parseTilesets);
                processElement(pElementRoot, "layer", pLevel, &LevelParser::parseTileLayer);
                processElement(pElementRoot, "objectgroups", pLevel, &LevelParser::parseObjects);
            }
            return pLevel;
        }
    }
    return nullptr;
}

void LevelParser::parseTilesets(XMLElement *pTilesetRoot, Level *pLevel) {
    LOG_INFO("Parsing tilesets");
    auto pTilesets = pLevel->getTilesets();
    std::string source;
    Tileset tileset{};

    for (auto a = pTilesetRoot->FirstAttribute(); a; a = a->Next()) {
        attributeToInt(a, "firstgid", &tileset.firstGridID);
        if (StringUtils::equalsIgnoreCase(a->Name(), "source")) { source = std::string(m_dir) + "/" + a->Value(); }
    }

    XMLDocument doc;
    auto result = doc.LoadFile(source.c_str());

    if (result == XML_SUCCESS) {
        auto pRoot = doc.RootElement();

        for (auto a = pRoot->FirstAttribute(); a; a = a->Next()) {
            attributeToString(a, "name", &tileset.name);
            attributeToInt(a, "tilewidth", &tileset.tileWidth);
            attributeToInt(a, "tileheight", &tileset.tileHeight);
            attributeToInt(a, "spacing", &tileset.spacing);
            attributeToInt(a, "margin", &tileset.margin);
            attributeToInt(a, "columns", &tileset.numColumns);
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
                    attributeToInt(a, "width", &tileset.width);
                    attributeToInt(a, "height", &tileset.height);
                }
            }

            LOG_INFO("Done creating tileset: " << tileset.name);
            pTilesets->push_back(tileset);
        }
    } else {
        LOG_ERROR("Error occurred: " << XMLDocument::ErrorIDToName(result));
    }
}

void LevelParser::parseTileLayer(XMLElement *pTileElement, Level *pLevel) {
    LOG_INFO("Parsing tile layers");
    auto pLayers = &pLevel->m_layers;
    auto pTilesets = &pLevel->m_tilesets;
    std::string name;

    for (auto a = pTileElement->FirstAttribute(); a; a = a->Next()) {
        attributeToString(a, "name", &name);
        attributeToInt(a, "width", &m_width);
        attributeToInt(a, "height", &m_height);
    }

    for (auto *pElementRoot = pTileElement->FirstChildElement(); pElementRoot != nullptr; pElementRoot = pElementRoot->NextSiblingElement()) {
        auto elementValue = std::string(pElementRoot->Value());
        if (StringUtils::equalsIgnoreCase(elementValue, "data")) {
            std::string encoding, compression;

            for (auto a = pElementRoot->FirstAttribute(); a; a = a->Next()) {
                attributeToString(a, "encoding", &encoding);
                attributeToString(a, "compression", &compression);
            }

            std::string encodedIDs = pElementRoot->FirstChild()->Value();
            std::string decodedIDs = base64_decode(StringUtils::trim(encodedIDs));

            auto data = prepareData();
            auto ids = prepareIds(decodedIDs);

            copyIdsToVector(data, ids);

            pLayers->push_back(new TileLayer(m_tileSize, *pTilesets, data));
        }
    }
}

void LevelParser::parseObjects(XMLElement *pTilesetRoot, Level *pLevel) {
    LOG_INFO("Parsing objects");

}

void LevelParser::attributeToInt(const XMLAttribute *a, const char *attrName, int *attr) const {
    if (StringUtils::equalsIgnoreCase(a->Name(), attrName)) { *attr = a->IntValue(); }
}

void LevelParser::attributeToString(const XMLAttribute *a, const char *attrName, std::string *attr) const {
    if (StringUtils::equalsIgnoreCase(a->Name(), attrName)) { *attr = a->Value(); }
}

std::vector<unsigned> LevelParser::prepareIds(const std::string &decodedIDs) const {
    uLongf numberOfIds = m_width * m_height * sizeof(int);
    std::vector<unsigned> ids(numberOfIds);

    uncompress((Bytef *) &ids[0], &numberOfIds, (const Bytef *) decodedIDs.c_str(), decodedIDs.size());
    return ids;
}

void LevelParser::copyIdsToVector(std::vector<std::vector<int>> &data, const std::vector<unsigned int> &gids) const {
    for (int rows = 0; rows < m_height; rows++) {
        for (int cols = 0; cols < m_width; cols++) {
            data[rows][cols] = gids[rows * m_width + cols];
        }
    }
}

std::vector<std::vector<int>> LevelParser::prepareData() const {
    std::vector<std::vector<int>> data;

    std::vector<int> layerRow(static_cast<unsigned long>(m_width));
    for (int j = 0; j < m_height; j++) {
        data.push_back(layerRow);
    }
    return data;
}

XMLError LevelParser::loadRootXML(const char *levelFile, XMLDocument &doc) {
    auto tempFilename = new char[strlen(levelFile) + 1];
    strncpy(tempFilename, levelFile, strlen(levelFile) + 1);

    auto temp = dirname(tempFilename);
    m_dir = new char[strlen(temp) + 1];
    strcpy(m_dir, temp);

    delete[] tempFilename;
    return doc.LoadFile(levelFile);
}

void LevelParser::processElement(XMLElement *pElementRoot, std::string elementValue, Level *pLevel, void (LevelParser::*fn)(XMLElement *, Level *)) {
    if (StringUtils::equalsIgnoreCase(pElementRoot->Name(), elementValue)) {
        (this->*fn)(pElementRoot, pLevel);
    }
}
