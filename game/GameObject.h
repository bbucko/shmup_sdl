#include <SDL.h>
#include <iostream>
#include <string>

#include "TextureManager.h"

#ifndef SHMUP_GAMEOBJECT_H
#define SHMUP_GAMEOBJECT_H

class GameObject {

protected:
    std::string m_textureID;
    int m_x;
    int m_y;

    int m_width;
    int m_height;

    int m_currentRow;
    int m_currentFrame;

public:
    virtual void load(int x, int y, int width, int height, std::string textureID);

    virtual void draw(SDL_Renderer *pRenderer);

    virtual void update()= 0;
};


#endif //SHMUP_GAMEOBJECT_H
