#include <SDL.h>
#include <SDL_image.h>
#include <map>

#ifndef SHMUP_TEXTUREMANAGER_H
#define SHMUP_TEXTUREMANAGER_H


class TextureManager {
private:
    std::map<std::string, SDL_Texture *> m_textureMap;

    TextureManager() = default;

public:
    bool load(std::string fileName, std::string id, SDL_Renderer *pRenderer);

    void draw(std::string id, int x, int y, int width, int height, SDL_Renderer *pRenderer,
              SDL_RendererFlip flip = SDL_FLIP_NONE);

    void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame,
                   SDL_Renderer *pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    static TextureManager *Instance();
};

#endif //SHMUP_TEXTUREMANAGER_H
