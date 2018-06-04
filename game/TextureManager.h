#ifndef SHMUP_TEXTUREMANAGER_H
#define SHMUP_TEXTUREMANAGER_H

#include <map>
#include <string>
#include <SDL.h>

class TextureManager {
private:
    std::map<std::string, SDL_Texture *> m_textureMap;

public:

    virtual bool load(std::string fileName, std::string id, SDL_Renderer *pRenderer);
    virtual void draw(std::string id, int x, int y, int width, int height, SDL_Renderer *pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    virtual void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    virtual void clear(std::string id);

    virtual ~TextureManager() {
        auto i = std::begin(m_textureMap);
        while (i != std::end(m_textureMap)) {
            SDL_DestroyTexture((*i).second);
            i = m_textureMap.erase(i);
        }
    };
};

#endif //SHMUP_TEXTUREMANAGER_H
