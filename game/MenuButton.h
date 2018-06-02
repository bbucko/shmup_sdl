#ifndef SHMUP_MENUBUTTON_H
#define SHMUP_MENUBUTTON_H

#include "sdl/SDLGameObject.h"

class MenuButton : public SDLGameObject {
public:
    virtual void draw();

    virtual void update();

    virtual void clean();

    explicit MenuButton(const LoaderParams *pParams) : SDLGameObject(pParams) {}

};


#endif //SHMUP_MENUBUTTON_H
