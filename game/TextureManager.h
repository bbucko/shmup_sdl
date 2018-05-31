#ifndef SHMUP_TEXTUREMANAGER_H
#define SHMUP_TEXTUREMANAGER_H

#include <SDL.h>
#include <string>
#include <map>

class TextureManager {
private:
    std::map<std::string, SDL_Texture *> m_textureMap;

    TextureManager() = default;

    ~TextureManager() = default;

public:
    bool load(std::string fileName, std::string id, SDL_Renderer *pRenderer);

    void draw(std::string id, int x, int y, int width, int height, SDL_Renderer *pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    static TextureManager &Instance() {
        static TextureManager instance;
        return instance;
    }
};

#endif //SHMUP_TEXTUREMANAGER_H
