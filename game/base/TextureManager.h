#ifndef SHMUP_TEXTUREMANAGER_H
#define SHMUP_TEXTUREMANAGER_H

using namespace std;

class TextureManager {
public:
    virtual bool load(const string &fileName, const string &id) = 0;

    virtual void clear(const string &id) = 0;

    virtual void draw(const string &id, int x, int y, int width, int height) const = 0;

    virtual void draw(const string &id, int x, int y, int width, int height, int currentRow, int currentFrame) const = 0;

    virtual void draw(const string &id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame) const = 0;

    virtual ~TextureManager() = default;
};


#endif //SHMUP_TEXTUREMANAGER_H
