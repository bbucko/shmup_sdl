#include "LevelParser.h"

#include <libgen.h>
#include <utils/Base64.h>
#include <utils/StringUtils.h>
#include <zlib.h>
#include <base/layers/BulletLayer.h>
#include "base/layers/ObjectLayer.h"
#include "ServiceLocator.h"
#include "base/layers/TileLayer.h"

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

            for (auto *pElementRoot = pRoot->FirstChildElement();
                 pElementRoot != nullptr; pElementRoot = pElementRoot->NextSiblingElement()) {
                processElement(pElementRoot, "tileset", pLevel, &LevelParser::parseTilesets);
                processElement(pElementRoot, "layer", pLevel, &LevelParser::parseTileLayer);
                processElement(pElementRoot, "objectgroup", pLevel, &LevelParser::parseObjectLayer);
            }
            return pLevel;
        }
    }
    return nullptr;
}

void LevelParser::parseObjectLayer(XMLElement *pObjectElement, Level *pLevel) {
    LOG_INFO("Parsing object layer");
    auto pObjectLayer = new ObjectLayer();
    for (auto *pElementRoot = pObjectElement->FirstChildElement();
         pElementRoot != nullptr; pElementRoot = pElementRoot->NextSiblingElement()) {
        std::string name, type, textureId;
        int id{0}, x{0}, y{0}, width{0}, height{0}, numFrames{0};

        for (auto *attribute = pElementRoot->FirstAttribute(); attribute; attribute = attribute->Next()) {
            attributeToInt(attribute, "id", &id);
            attributeToInt(attribute, "x", &x);
            attributeToInt(attribute, "y", &y);
            attributeToString(attribute, "name", &name);
            attributeToString(attribute, "type", &type);
        }

        for (auto *pPropertiesRoot = pElementRoot->FirstChildElement();
             pPropertiesRoot != nullptr; pPropertiesRoot = pPropertiesRoot->NextSiblingElement()) {
            for (auto *pPropertyElement = pPropertiesRoot->FirstChildElement();
                 pPropertyElement != nullptr; pPropertyElement = pPropertyElement->NextSiblingElement()) {
                const char *attrName = pPropertyElement->Attribute("name");
                if (StringUtils::equalsIgnoreCase(attrName, "textureID")) {
                    textureId = pPropertyElement->Attribute("value");
                }
                if (StringUtils::equalsIgnoreCase(attrName, "numFrames")) {
                    numFrames = pPropertyElement->IntAttribute("value");
                }
                if (StringUtils::equalsIgnoreCase(attrName, "width")) {
                    width = pPropertyElement->IntAttribute("value");
                }
                if (StringUtils::equalsIgnoreCase(attrName, "height")) {
                    height = pPropertyElement->IntAttribute("value");
                }
            }
        }

        auto pGameObject = ServiceLocator::gameObjectFactory()->create(id, type);
        if (pGameObject == nullptr) {
            LOG_ERROR("invalid type: " << type);
            break;
        }
        pGameObject->load(std::make_unique<LoaderParams>(x, y, width, height, numFrames, textureId));

        pObjectLayer->getObjects()->push_back(pGameObject);
    }
    pLevel->m_layers.push_back(pObjectLayer);
    pLevel->m_layers.push_back(new BulletLayer());
}

void LevelParser::parseTextures(XMLElement *pTextureRoot) {
    std::string value;
    std::string name;
    for (auto attribute = pTextureRoot->FirstAttribute(); attribute; attribute = attribute->Next()) {
        attributeToString(attribute, "value", &value);
        attributeToString(attribute, "name", &name);
    }

    ServiceLocator::textureManager()->load(std::string(m_dir) + "/" + value, name);
}

void LevelParser::parseTilesets(XMLElement *pTilesetRoot, Level *pLevel) {
    LOG_INFO("Parsing tilesets");
    auto pTilesets = &pLevel->m_tilesets;
    std::string source;
    Tileset tileset{};

    for (auto attribute = pTilesetRoot->FirstAttribute(); attribute; attribute = attribute->Next()) {
        attributeToInt(attribute, "firstgid", &tileset.firstGridID);
        if (StringUtils::equalsIgnoreCase(attribute->Name(), "source")) {
            source = std::string(m_dir) + "/" + attribute->Value();
        }
    }

    XMLDocument doc;
    auto result = doc.LoadFile(source.c_str());

    if (result == XML_SUCCESS) {
        auto pRoot = doc.RootElement();

        for (auto attribute = pRoot->FirstAttribute(); attribute; attribute = attribute->Next()) {
            attributeToString(attribute, "name", &tileset.name);
            attributeToInt(attribute, "tilewidth", &tileset.tileWidth);
            attributeToInt(attribute, "tileheight", &tileset.tileHeight);
            attributeToInt(attribute, "spacing", &tileset.spacing);
            attributeToInt(attribute, "margin", &tileset.margin);
            attributeToInt(attribute, "columns", &tileset.numColumns);
        }

        for (auto *pElementRoot = pRoot->FirstChildElement();
             pElementRoot != nullptr; pElementRoot = pElementRoot->NextSiblingElement()) {
            auto elementValue = std::string(pElementRoot->Value());
            if (StringUtils::equalsIgnoreCase(elementValue, "image")) {
                for (auto attribute = pElementRoot->FirstAttribute(); attribute; attribute = attribute->Next()) {
                    if (StringUtils::equalsIgnoreCase(attribute->Name(), "source")) {
                        auto imageFilename = std::string(m_dir) + "/" + attribute->Value();
                        LOG_INFO("Loading image: " << tileset.name << " from file: " << imageFilename);

                        ServiceLocator::textureManager()->load(imageFilename, tileset.name);
                    }
                    attributeToInt(attribute, "width", &tileset.width);
                    attributeToInt(attribute, "height", &tileset.height);
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
    auto layers = &pLevel->m_layers;
    auto tilesets = &pLevel->m_tilesets;
    std::string name;

    for (auto attribute = pTileElement->FirstAttribute(); attribute; attribute = attribute->Next()) {
        attributeToString(attribute, "name", &name);
        attributeToInt(attribute, "width", &m_width);
        attributeToInt(attribute, "height", &m_height);
    }

    for (auto *pElementRoot = pTileElement->FirstChildElement();
         pElementRoot != nullptr; pElementRoot = pElementRoot->NextSiblingElement()) {
        auto elementValue = std::string(pElementRoot->Value());
        if (StringUtils::equalsIgnoreCase(elementValue, "data")) {
            std::string encoding, compression;

            for (auto attribute = pElementRoot->FirstAttribute(); attribute; attribute = attribute->Next()) {
                attributeToString(attribute, "encoding", &encoding);
                attributeToString(attribute, "compression", &compression);
            }

            std::string encodedIDs = pElementRoot->FirstChild()->Value();
            std::string decodedIDs = base64_decode(StringUtils::trim(encodedIDs));

            auto data = prepareData();
            auto ids = prepareIds(decodedIDs);

            copyIdsToVector(data, ids);

            layers->push_back(new TileLayer(m_tileSize, m_width, m_height, *tilesets, data));
        }
    }
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

void LevelParser::processElement(XMLElement *pElementRoot, std::string elementValue, Level *pLevel,
                                 void (LevelParser::*fn)(XMLElement *, Level *)) {
    if (StringUtils::equalsIgnoreCase(pElementRoot->Name(), elementValue)) {
        (this->*fn)(pElementRoot, pLevel);
    }
}
