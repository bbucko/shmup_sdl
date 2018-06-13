#ifndef SHMUP_TEXTUREMANAGER_H
#define SHMUP_TEXTUREMANAGER_H

#include <SDL.h>
#include <map>
#include <string>
#include "Game.h"

class TextureManager {
private:
    std::map<std::string, SDL_Texture *> m_textureMap;

public:
    virtual bool load(const std::string &fileName, std::string id, Renderer *pRenderer);

    virtual void draw(const std::string &id, int x, int y, int width, int height, Renderer *pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    virtual void drawFrame(const std::string &id, int x, int y, int width, int height, int currentRow, int currentFrame, Renderer *pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    virtual void clear(const std::string &id);

    virtual void drawTile(const std::string &id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, Renderer *pRenderer);

    virtual ~TextureManager() {
        auto i = std::begin(m_textureMap);
        while (i != std::end(m_textureMap)) {
            SDL_DestroyTexture((*i).second);
            i = m_textureMap.erase(i);
        }
    };
};

#endif  // SHMUP_TEXTUREMANAGER_H
