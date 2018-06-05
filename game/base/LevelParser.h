#ifndef SHMUP_LEVELPARSER_H
#define SHMUP_LEVELPARSER_H

class LevelParser {
private:
    LevelParser() = default;

    ~LevelParser() = default;

public:
    static LevelParser &Instance() {
        static LevelParser instance;
        return instance;
    }

    void parseLevel(const char *levelFile);
};


#endif //SHMUP_LEVELPARSER_H
