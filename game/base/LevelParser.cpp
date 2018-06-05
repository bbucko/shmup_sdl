#include <utils/Logger.h>
#include "LevelParser.h"
#include <tinyxml2.h>

using namespace tinyxml2;

void LevelParser::parseLevel(const char *levelFile) {
    LOG_INFO("Load level " << levelFile);
    XMLDocument doc;
    doc.LoadFile(levelFile);

}
