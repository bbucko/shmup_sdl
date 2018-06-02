#ifndef SHMUP_MENUBUTTON_H
#define SHMUP_MENUBUTTON_H

#include "sdl/SDLGameObject.h"

class MenuButton : public SDLGameObject {
public:
    void draw() override;

    void update() override;

    void clean() override;

    void load(const LoaderParams *pParams) override;

};


#endif //SHMUP_MENUBUTTON_H
