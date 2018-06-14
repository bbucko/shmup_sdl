#include "SDLTextureManager.h"

#include <SDL_image.h>
#include <base/ServiceLocator.h>

bool SDLTextureManager::load(const std::string &fileName, const std::string &id) {
    SDL_Surface *pTempSurface = IMG_Load(fileName.c_str());

    if (pTempSurface == nullptr) {
        LOG_ERROR("Missing image: " << fileName);
        return false;
    }
    SDL_Texture *pTexture = SDL_CreateTextureFromSurface(m_sdlRenderer, pTempSurface);

    SDL_FreeSurface(pTempSurface);

    if (pTexture != nullptr) {
        LOG_INFO("Saving image under id: " << id);
        m_textureMap[id] = pTexture;
        return true;
    }

    return false;
}

void SDLTextureManager::draw(const std::string &id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame) const {
    const auto value = m_textureMap.find(id);
    if (value == m_textureMap.end()) LOG_ERROR("No such texture: " << id);

    SDL_Rect srcRect;
    SDL_Rect dstRect;

    srcRect.x = margin + (spacing + width) * currentFrame;
    srcRect.y = margin + (spacing + height) * currentRow;
    srcRect.w = dstRect.w = width;
    srcRect.h = dstRect.h = height;

    dstRect.x = x;
    dstRect.y = y;

    SDL_RenderCopyEx(m_sdlRenderer, value->second, &srcRect, &dstRect, 0, nullptr, SDL_FLIP_NONE);
}

void SDLTextureManager::clear(const std::string &id) {
    auto texture = m_textureMap[id];
    SDL_DestroyTexture(texture);
    m_textureMap.erase(id);
}
