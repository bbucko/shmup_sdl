#ifndef SHMUP_MENUBUTTON_H
#define SHMUP_MENUBUTTON_H

#include <base/GameObjectFactory.h>
#include "sdl/SDLGameObject.h"

class MenuButton : public SDLGameObject {
public:
    explicit MenuButton(int id) : SDLGameObject(id) {}

    void draw() override ;

    void update() override;

    void clean() override;

    void load(std::unique_ptr<LoaderParams> pParams) override;
};

class MenuButtonCreator : public BaseCreator {
    GameObject *createGameObject(int id) const override {
        return new MenuButton(id);
    }
};

#endif  // SHMUP_MENUBUTTON_H
