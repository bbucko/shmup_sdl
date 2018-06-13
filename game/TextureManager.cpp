#include "TextureManager.h"

#include <SDL_image.h>

bool TextureManager::load(const std::string &fileName, std::string id, SDL_Renderer *pRenderer) {
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

void TextureManager::draw(const std::string &id, int x, int y, int width, int height, SDL_Renderer *pRenderer, SDL_RendererFlip flip) {
    drawFrame(id, x, y, width, height, 0, 0, pRenderer, flip);
}

void TextureManager::drawFrame(const std::string &id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer, SDL_RendererFlip flip) {
    if (m_textureMap[id] == nullptr) LOG_ERROR("No such texture: " << id);

    int spacing = 1;
    int margin = 1;

    SDL_Rect srcRect;
    SDL_Rect dstRect;

    srcRect.x = margin + (spacing + width) * currentFrame;
    srcRect.y = margin + (spacing + height) * currentRow;
    srcRect.w = dstRect.w = width;
    srcRect.h = dstRect.h = height;

    dstRect.x = x;
    dstRect.y = y;

    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::clear(const std::string &id) {
    auto texture = m_textureMap[id];
    SDL_DestroyTexture(texture);
    m_textureMap.erase(id);
}

void TextureManager::drawTile(const std::string &id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, Renderer *pRenderer) {
    SDL_Rect srcRect;
    SDL_Rect dstRect;
    srcRect.x = margin + (spacing + width) * currentFrame;
    srcRect.y = margin + (spacing + height) * currentRow;
    srcRect.w = dstRect.w = width;
    srcRect.h = dstRect.h = height;
    dstRect.x = x;
    dstRect.y = y;

    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &dstRect, 0, nullptr, SDL_FLIP_NONE);
}
