#include "TextureManager.h"
#include "Game.h"

#include <SDL_image.h>

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer *pRenderer) {
    SDL_Surface *pTempSurface = IMG_Load(fileName.c_str());

    if (pTempSurface == nullptr) {
        std::cerr << "Missing image: " << fileName << std::endl;
        return false;
    }

    SDL_Texture *pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

    SDL_FreeSurface(pTempSurface);

    if (pTexture != nullptr) {
        LOG("Saving image under id: ");
        m_textureMap[id] = pTexture;
        return true;
    }

    return false;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer *pRenderer, SDL_RendererFlip flip) {
    drawFrame(id, x, y, width, height, 0, 0, pRenderer, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer, SDL_RendererFlip flip) {

    if (m_textureMap[id] == nullptr) {
        std::cerr << "No such texture: " << id << std::endl;
    }

    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = currentFrame * width;
    srcRect.y = (currentRow) * height;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;

    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}