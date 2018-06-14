#ifndef SHMUP_SDLTEXTUREMANAGER_H
#define SHMUP_SDLTEXTUREMANAGER_H

#include <SDL.h>
#include <map>
#include <string>
#include <Game.h>
#include <base/TextureManager.h>

using namespace std;

class SDLTextureManager : public TextureManager {
public:

    explicit SDLTextureManager(SDL_Renderer *sdlRenderer) : m_sdlRenderer(sdlRenderer) {};

    bool load(const string &fileName, const string &id) override;

    void clear(const string &id) override;

    void draw(const string &id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame) const override;

    void draw(const std::string &id, int x, int y, int width, int height) const override {
        draw(id, x, y, width, height, 0, 0);
    }

    void draw(const std::string &id, int x, int y, int width, int height, int currentRow, int currentFrame) const override {
        draw(id, 1, 1, x, y, width, height, currentRow, currentFrame);
    }

    ~SDLTextureManager() {
        for (auto i: m_textureMap) {
            SDL_DestroyTexture(i.second);
        }
        m_textureMap.clear();
    };

private:
    map<string, SDL_Texture *> m_textureMap;
    SDL_Renderer *m_sdlRenderer;
};

#endif  // SHMUP_SDLTEXTUREMANAGER_H
