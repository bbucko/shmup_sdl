#include "TextureManager.h"
#include "Game.h"

#include <SDL_image.h>

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer *pRenderer) {
    SDL_Surface *pTempSurface = IMG_Load(fileName.c_str());

    if (pTempSurface == nullptr) {
        LOG_ERROR("Missing image: " << fileName);
        return false;
    }

    SDL_Texture *pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

    SDL_FreeSurface(pTempSurface);

    if (pTexture != nullptr) {
        LOG_INFO("Saving image under id: " << id);
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
        LOG_ERROR("No such texture: " << id);
    }

    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = currentFrame * width;
    srcRect.y = (currentRow) * height;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;

    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, nullptr, flip);
}

void TextureManager::clear(std::string id) {
    m_textureMap.erase(id);
}
