#ifndef SHMUP_MENUBUTTON_H
#define SHMUP_MENUBUTTON_H

#include <base/GameObjectFactory.h>
#include "sdl/SDLGameObject.h"

class MenuButton : public SDLGameObject {
public:
    void draw() override;

    void update() override;

    void clean() override;

    void load(std::unique_ptr<LoaderParams> const &pParams) override;
};

class MenuButtonCreator : public BaseCreator {
    GameObject *createGameObject() const override {
        return new MenuButton();
    }
};

#endif  // SHMUP_MENUBUTTON_H
