#include "Game.h"

int main() {
    Game *pGame = Game::Instance();

    pGame->init();
    while (pGame->running()) {
        pGame->handleEvents();
        pGame->update();
        pGame->render();
    }

    pGame->terminate();
}
