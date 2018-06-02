#include <SDL_events.h>
#include <Game.h>
#include "InputHandler.h"

void InputHandler::onKeyDown() {
    m_keystates = SDL_GetKeyboardState(0);
}

void InputHandler::onKeyUp() {

}

bool InputHandler::isKeyDown(SDL_Scancode key) const {
    if (m_keystates != nullptr) {
        return m_keystates[key] == 1;
    }

    return false;
}

void InputHandler::update() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                Game::Instance().quit();
                break;
            case SDL_KEYDOWN:
                onKeyDown();
                break;

            case SDL_KEYUP:
                onKeyUp();
                break;

            default:
                break;
        }
    }
}
