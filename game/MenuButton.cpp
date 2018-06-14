#include "MenuButton.h"

void MenuButton::draw() {
    SDLGameObject::draw();
}

void MenuButton::update() {
    SDLGameObject::update();
}

void MenuButton::clean() {
    SDLGameObject::clean();
}

void MenuButton::load(std::unique_ptr<LoaderParams> pParams) {
    SDLGameObject::load(std::move(pParams));
}
